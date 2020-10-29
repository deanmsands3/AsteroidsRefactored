#ifndef GAME_H
#define GAME_H
#include "Animation.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>


using json = nlohmann::json;

class Game
{
    public:
        /** Default constructor */
        Game(const std::string &json_file);
        /** Default destructor */
        virtual ~Game();

        /** Access _textures
         * \return The current value of _textures
         */
        sf::Texture getTexture(const std::string &texture_name);

        /** Set _textures
         * \param val New value to set
         */
        void setTexture(std::string texture_name, const sf::Texture &val);

        /** Access _animations
         * \return The current value of _animations
         */
        Animation getAnimation(std::string animation_name);

        /** Set _animations
         * \param val New value to set
         */
        void setAnimation(std::string animation_name, const Animation &val);

        /** Access _entities
         * \return The current value of _entities
         */
        std::shared_ptr<Entity> getEntity(unsigned long long entity_id);

        /** Set _entities
         * \param val New value to set
         */
        void setEntity(unsigned long long entity_id, std::shared_ptr<Entity> val);

        virtual void play();
    protected:
        std::unordered_map<unsigned long long, std::shared_ptr<Entity> > _entities; //!< Member variable "_entities"
        sf::RenderWindow _window; //!< Member variable "_window"
        void addEntity(unsigned long long entity_id, std::shared_ptr<Entity> entity);
        void delEntity(unsigned long long entity_id);
        json loadJSON(const std::string &json_file);
        void loadTextures(const json &index);
        void loadAnimations(const json &index);
        void loadEntities(const json &index);
        virtual void setup();
        virtual void loop();
        virtual void innerLoop();
        virtual void handleInput();
        virtual void gameLogic();
        virtual void updateEntities();
        virtual void cleanupEntities();
        virtual void draw();
        virtual void cleanup();
    private:
        std::unordered_map<std::string, sf::Texture> _textures; //!< Member variable "_textures"
        std::unordered_map<std::string, Animation> _animations; //!< Member variable "_animations"
};

#endif // GAME_H
