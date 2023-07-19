#include "Environment.h"

Environment::Environment(std::function<void(int)> callback, std::shared_ptr<AssetManager> am)
{
   this->am = am;
   this->sm_callback = callback;
   tree = *am->get_texture("tree.png");
   water = *am->get_texture("tree.png");
   mountain = *am->get_texture("mountain.png");
   rock = *am->get_texture("mountain.png");
   std::shared_ptr<sf::Texture> text = am->get_texture("engine.png");
   this->ship = Ship(am->get_texture("engine.png"));
   this->player = PlayerCharacter();
   main = PlanetSystem();
   camera = sf::View(sf::FloatRect(0.0f, 0.0f, 1280.0f, 720.0f));
}

void Environment::process()
{
   process_planets();
   process_player();
   process_camera();
   ship.move(ship.movement);
   player.move(player.movement);
}
void Environment::process_planets()
{
   for (auto& element : this->main.planets) {
      v2f old_pos = element.getPosition();
      element.rad += 0.0001f;
      element.setPosition(v2f(element.orbit_radius * cos(element.rad), element.orbit_radius * sin(element.rad)));
      v2f delta = element.getPosition() - old_pos;
      element.movement = delta;
      for (auto& obj : element.objects) {
         obj.setPosition(element.planet.getPosition() + v2f(sin(toRad(obj.ang_pos)) * (element.planet.getRadius() + getSize(obj.type, v2f(0, 0)).y),
            -cos(toRad(obj.ang_pos)) * (element.planet.getRadius() + getSize(obj.type, v2f(0, 0)).y)));
      }
   }
}

void Environment::process_player()
{
   process_player_matrix();
   ship.o_acceleration = NULL_VEC;
   ship.gravity_acceleration = NULL_VEC;
   player.gravity_acceleration = NULL_VEC;
   player.o_acceleration = NULL_VEC;

   for (auto& element : this->main.planets) {
      gravity_forces(element, ship);
   }
   for (const auto& element : main.planets) {
      if (check_collisions(ship.fueltank, ship.t_fueltank, element.planet) ||
         check_collisions(ship.engine_collider, ship.t_engine, element.planet)
         || check_collisions(ship.nose, ship.t_nose, element.planet)) {
         ship.gravity_acceleration = NULL_VEC;
         ship.movement = element.movement;
      }
   }
   if (ship.engine.isWorking && ship.engine.fuel >= 0.0f) {
      const float power = 10.0f;
      ship.o_force = (v2f(power * sin(toRad(ship.getRotation())), -power * cos(toRad(ship.getRotation()))));
      ship.o_acceleration = (ship.o_force / ship.mass);
      ship.engine.fuel -= 0.01f;
   }
   else {
      ship.o_acceleration = NULL_VEC
   }

   //CHARACTER
   float mov = 40.0f;
   float deg = 90.0f;
   for (auto& element : main.planets) {
      gravity_forces(element, player);
   }
   player.setRotation(atgrav(player.getPosition() - main.planets[0].getPosition()) + 180.0f);
   for (const auto& element : main.planets) {
      if (check_collisions(player.player_c, player.t, element.planet)) {
         player.gravity_acceleration = NULL_VEC;
         player.movement = element.movement;
      }
   }
   //STEROWANIE
   if (player.mdir.x == 1.0f) {
      deg = -90.0f;
   }
   else if (player.mdir.x == -1.0f) {
      deg = 90.0f;
   }
   else mov = 0.0f;
   ship.movement += ship.o_acceleration + ship.gravity_acceleration;
   ship.engine.isWorking = false;
   player.mdir = NULL_VEC;
   v2f walk_movement = (v2f(mov * sin(toRad(player.getRotation() + deg)), -mov * cos(toRad(player.getRotation() + deg))));
   player.move(walk_movement);
   player.movement += player.gravity_acceleration + player.o_acceleration;
}
void Environment::process_input()
{
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::O) && (cloc.getElapsedTime() - last_press).asSeconds() >= 0.5f) {
      std::cout << (cloc.getElapsedTime() - last_press).asSeconds() << std::endl;
      camera.zoom(0.25f);
      last_press = cloc.getElapsedTime();
   }
   else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && (cloc.getElapsedTime() - last_press).asSeconds() >= 0.5f) {
      std::cout << (cloc.getElapsedTime() - last_press).asSeconds() << std::endl;
      camera.zoom(2.0f);
      last_press = cloc.getElapsedTime();
   }
   else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && (cloc.getElapsedTime() - last_press).asSeconds() >= 0.5f)
   {
      is_player_out = !is_player_out;
      player.setPosition(ship.fueltank.getPosition());
      player.movement = ship.movement;
      last_press = cloc.getElapsedTime();
   }
   else if (!is_player_out) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
         ship.rotate(50.0f / 60.0f);
         //this.camera.rotate(50.0f / 60.0f);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
         ship.rotate(-50.0f / 60.0f);
         //this.camera.rotate(-50.0f / 60.0f);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
         this->camera.rotate(50.0f / 60.0f);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
         this->camera.rotate(-50.0f / 60.0f);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && ship.engine.throttle <= 1.0f) {
         ship.engine.throttle += 0.5f / 60.0f;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && ship.engine.throttle >= 0.0f) {
         ship.engine.throttle -= 0.5f / 60.0f;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (cloc.getElapsedTime() - last_press).asSeconds() >= 0.5f) {
         ship.engine.isWorking = true;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && (cloc.getElapsedTime() - last_press).asSeconds() >= 0.5f) {
         ship.movement = NULL_VEC;
         last_press = cloc.getElapsedTime();
      }
   }
   else {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
         player.mdir = v2f(1.0f, 0.0f);
         //this.camera.rotate(50.0f / 60.0f);
      }
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
         player.mdir = v2f(-1.0f, 0.0f);
         //this->camera.rotate(-50.0f / 60.0f);
      }
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
         player.mdir.y = 1.0f;
      }
   }
}
sf::Vector2u Environment::getSize(int type, v2f scale)
{
   if (type == WATER)
      return water.getSize();
   if (type == TREE)
      return tree.getSize();
   if (type == ROCK)
      return rock.getSize();
   if (type == MOUNTAIN)
      return mountain.getSize();
}
void Environment::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   std::vector<sf::Text> player_info;
   sf::Font font = *am->get_font("arial.ttf");
   player_info.push_back(sf::Text("Fuel: " + std::to_string(ship.engine.fuel), font, 20));

   player_info.push_back(sf::Text("Velocity: " + std::to_string(ship.movement.x) + ", " +
      std::to_string(ship.movement.y), font, 20));

   player_info.push_back(sf::Text("Position: " + std::to_string(ship.fueltank.getPosition().x) + ", " +
      std::to_string(ship.fueltank.getPosition().y), font, 20));

   v2f move = NULL_VEC;
   target.setView(camera);
   sf::Sprite s;
   s.setTexture(tree);
   //mozesz zrobic overloada dla calego enviorment
   for (auto element : main.planets) {
      target.draw(element.atmosphere);
      target.draw(element.planet);
      for (auto& obj : element.objects) {
         if (obj.type == WATER)
            s.setTexture(water);
         if (obj.type == TREE)
            s.setTexture(tree);
         if (obj.type == ROCK)
            s.setTexture(rock);
         if (obj.type == MOUNTAIN)
            s.setTexture(mountain);
         s.setPosition(obj.pos);
         s.setRotation(obj.ang_pos);
         target.draw(s);
      }
   }
   target.draw(main.main_planet);
   if (is_player_out)
      target.draw(player);
   target.draw(ship);


   //misc
   for (auto element : v) {
      sf::CircleShape c(5.0f);
      c.setPosition(element);
      c.setFillColor(sf::Color::Red);
      target.draw(c);
   }
   target.setView(sf::View(sf::FloatRect(0.0f, 0.0f, 1280.0f, 720.0f)));
   for (auto element : player_info) {
      element.setPosition(v2f(0, 0) + move);
      target.draw(element);
      move += v2f(0, 30);
   }
}
void Environment::process_player_vertices()
{
   v = obtain_vertices(ship.fueltank, ship.t_fueltank);
   std::vector<v2f> v1 = obtain_vertices(ship.engine_collider, ship.t_engine);
   std::vector<v2f> v2 = obtain_vertices(ship.nose, ship.t_nose);
   std::vector<v2f> v3 = obtain_vertices(player.player_c, player.t);
   for (auto element : v1) {
      v.push_back(element);
   }
   for (auto element : v2) {
      v.push_back(element);
   }
   for (auto element : v3) {
      v.push_back(element);
   }
}
void Environment::process_camera()
{
   if (is_player_out) {
      camera.setCenter(player.player_c.getPosition());
      camera.setRotation(player.getRotation());
   }
   else {
      camera.setCenter(ship.getPosition());
   }
}
void Environment::process_player_matrix()
{
   ship.t_engine = sf::Transform();
   ship.t_fueltank = sf::Transform();
   ship.t_nose = sf::Transform();

   ship.t_engine.translate(ship.engine_sprite.getPosition() - ship.engine_sprite.getOrigin());
   ship.t_engine.translate(v2f(0, -260) + ship.engine_sprite.getOrigin());
   ship.t_engine.rotate(ship.getRotation());
   ship.t_engine.translate(v2f(0, 260) - ship.engine_sprite.getOrigin());

   ship.t_fueltank.translate(ship.fueltank.getPosition() - ship.fueltank.getOrigin());
   ship.t_fueltank.translate(ship.fueltank.getOrigin());
   ship.t_fueltank.rotate(ship.getRotation());
   ship.t_fueltank.translate(-ship.fueltank.getOrigin());

   ship.t_nose.translate(ship.nose.getPosition() - ship.nose.getOrigin());
   ship.t_nose.translate(v2f(0, 200) + ship.nose.getOrigin());
   ship.t_nose.rotate(ship.getRotation());
   ship.t_nose.translate(v2f(0, -200) - ship.nose.getOrigin());

   player.t = sf::Transform();
   player.t.translate(player.player_c.getPosition() - player.player_c.getOrigin());
   player.t.translate(player.player_c.getOrigin());
   player.t.rotate(player.rotation);
   player.t.translate(-player.player_c.getOrigin());
}
void Environment::on_load()
{
   process_planets();
   v2f planet_position = main.planets[0].planet.getPosition();

   float radius = main.planets[0].planet.getRadius() + 1000.0f;
   float angular_position = rand() % 360;
   ship.setPosition(v2f(planet_position.x + radius * sin(toRad(angular_position)), planet_position.y + radius * cos(toRad(angular_position))));
   player.setPosition(v2f(planet_position.x + radius * sin(toRad(angular_position)), planet_position.y + radius * cos(toRad(angular_position))));
   gravity_forces(main.planets[0], ship);
   ship.movement = main.planets[0].movement;
   player.movement = ship.movement;
   ship.rotate(atgrav(ship.gravity_acceleration));
   camera.rotate(atgrav(ship.gravity_acceleration));
}