/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */

/**
 * @file Game.cpp
 * @brief Implementation of Game class methods.
 */
#include "Game.h"

Game::Game(){
    generate_game();
    initializeDamageCallbacks();
}

void Game::generate_game() {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < 9; ++i) {
        if (i == 4) {
            game[i] = std::make_unique<Player>(i, "Hero", 800, 1000);
            player = static_cast<Player*>(game[i].get());
        } else {
            generatecard(i);
        }
    }
    clean();
    draw();
}

void Game::update() {
    _STATUS.StepsUp();
    if (!isPlayerAlive()) {
        gameOver = true;
        return;
    }
    for (auto& obj : game) {
        if (obj) {
            obj->update();
        }
    }
    for (int i = 0; i < 9; ++i) {
        if (game[i]) {
            game[i]->takeDamage(0, DamageType::NORMAL); 
        }
    }
    checkAndConvertGoldToRubies();
    if (!isPlayerAlive()) {
        gameOver = true;
    }
}

bool Game::isGameOver() const { return gameOver; }

// Converts lines of gold to rubies 
void Game::checkAndConvertGoldToRubies() {
    std::vector<std::vector<int>> lines = {
        {0, 1, 2},  
        {3, 4, 5},  
        {6, 7, 8},  
        {0, 3, 6}, 
        {1, 4, 7},  
        {2, 5, 8}  
    };

    std::set<int> positionsToConvert;

    for (const auto& line : lines) {
        bool allGold = true;
        for (int pos : line) {
            if (!game[pos] || game[pos]->returntype() != ObjectType::GOLD) {
                allGold = false;
                break;
            }
        }
        if (allGold) {
            for (int pos : line) {
                positionsToConvert.insert(pos);
            }
        }
    }

    for (int pos : positionsToConvert) {
        Gold* gold = dynamic_cast<Gold*>(game[pos].get());
        if (gold) {
            int amount = gold->getAmount();
            game[pos] = std::make_unique<Ruby>(pos, amount);
            game[pos]->setOnDamageCallback([this](int pos, DamageType type) {
                this->handleObjectDamage(pos, type);
            });
        }
    }
}

// Renders the 3x3 game grid
void Game::draw() {
    const std::string EMPTY_LINE = std::string(CELL_WIDTH, ' ');
    const std::string HORIZONTAL_BORDER = "━━━━━━━━━━━━━━━━━━━━━━━━";
    
    for (int row = 0; row < 3; ++row) {

        for (int col = 0; col < 3; ++col) {
            int index = row * 3 + col;
            std::string color = game[index] ? game[index]->print().color : Color::MAGENTA;
            std::cout << color << "┏" << HORIZONTAL_BORDER << "┓" << Color::RESET << "   ";
        }
        std::cout << "\n";
        
        for (int line = 0; line < 10; ++line) {
            for (int col = 0; col < 3; ++col) {
                int index = row * 3 + col;
                DisplayInfo cell = game[index] ? game[index]->print() 
                                              : DisplayInfo{"Empty", "", "", Color::MAGENTA};
                
                std::string content;
                switch(line) {
                    case 2: content = centerText(cell.header, CELL_WIDTH); break;
                    case 4: content = centerText(cell.status, CELL_WIDTH); break;
                    case 6: content = centerText(cell.details, CELL_WIDTH); break;
                    default: content = EMPTY_LINE;
                }
                
                std::cout << cell.color << "┃" << content << "┃   " << Color::RESET;
            }
            std::cout << "\n";
        }
        
        for (int col = 0; col < 3; ++col) {
            int index = row * 3 + col;
            std::string color = game[index] ? game[index]->print().color : Color::MAGENTA;
            std::cout << color << "┗" << HORIZONTAL_BORDER << "┛" << Color::RESET << "   ";
        }
        std::cout << "\n\n";
    }
    
    std::cout << _STATUS.print();
}

void Game::clean(){
    std::cout << "\033[2J\033[1;1H"; 
}

// Handles player input and movement
void Game::handleInput(char input) {
    std::map<char, int> directionMap = {{'w', 0}, {'d', 1}, {'s', 2}, {'a', 3}};
    auto it = directionMap.find(input);
    if (it != directionMap.end()) {

        int direction = it->second;
        if (player->possibletomove(direction)) { 
            int poswheremove = player->getTargetPosition(direction);
            if (!game[poswheremove]) return;
            int playerpos = player->getPosition();
            switch(game[poswheremove]->returnInteractionType()){
                case InteractionType::IMMEDIATE_PASS:
                    handleIMMEDIATE_PASS(playerpos, poswheremove);
                    break;
                case InteractionType::SWAP_REQUIRED:
                    handleSWAP_REQUIRED(playerpos, poswheremove);
                    break;
                case InteractionType::TRIGGER_ON_STAY:
                    handleTRIGGER_ON_STAY(poswheremove);
                    break;
                case InteractionType::COMBAT_DEPENDENT:
                    handleCOMBAT_DEPENDENT(playerpos, poswheremove);
                    break;
            }
            
            update();
        }
    } else {
        std::cout << "Unknown key: " << input << std::endl;
    }
}

void Game::switchcards(int pos1, int pos2){ 
    std::unique_ptr<Object> temp = std::move(game[pos2]);
    game[pos2] = std::move(game[pos1]);
    game[pos1] = std::move(temp);
    game[pos1]->setPosition(pos1);
    game[pos2]->setPosition(pos2);
}

void Game::movecard(int pos, int direction){ 
    game[pos]->move(direction);
    game[game[pos]->getPosition()] = std::move(game[pos]);

}

// Complex grid shifting logic
void Game::gotodir(int direction){ 
    if (player->possibletomove((direction+2)%4)){
        int temp = player->getTargetPosition((direction+2)%4);
        movecard(player->getPosition(), direction);
        movecard(temp, direction);
        generatecard(temp);

    }else{
        if (player->possibletomove((direction+1)%4)){ 
            if (player->possibletomove((direction+3)%4)){
                int temp = player->getTargetPosition((direction+1)%4);
                movecard(player->getPosition(), direction);
                movecard(temp, (direction+3)%4);
                generatecard(temp);
            }else{
                int temp = player->getTargetPosition((direction+1)%4);
                int temp2 = game[temp]->getTargetPosition((direction+1)%4);
                movecard(player->getPosition(), direction);
                movecard(temp, (direction+3)%4);
                movecard(temp2, (direction+3)%4);
                generatecard(temp2);
            }
        }else if (player->possibletomove((direction+3)%4)){
            int temp = player->getTargetPosition((direction+3)%4);
            int temp2 = game[temp]->getTargetPosition((direction+3)%4);
            movecard(player->getPosition(), direction);
            movecard(temp, (direction+1)%4);
            movecard(temp2, (direction+1)%4);
            generatecard(temp2);
        }
    }
}

void Game::generatecard(int pos) {
    if (pos < 0 || pos >= 9) {
        std::cerr << "Invalid position in generatecard: " << pos << std::endl;
        return;
    }
    std::unique_ptr<Object> newCard = _STATUS.generateCard(pos);
    if (newCard) {
        newCard->setOnDamageCallback([this](int pos, DamageType type) {
            this->handleObjectDamage(pos, type);
        });
    }
    
    game[pos] = std::move(newCard);
}

// Handles immediate pass interactions
void Game::handleIMMEDIATE_PASS(int pos1, int pos2) { 
    if (pos1 != player->getPosition()) return;
    Object* obj = game[pos2].get();
    if (!obj) {
        std::cerr << "ERROR: Null object at position " << pos2 << std::endl;
        return;
    }
    switch (obj->returntype()) { 
        case ObjectType::WEAPON:
            {
                Weapon* weapon = dynamic_cast<Weapon*>(obj);
                if (weapon) {
                    player->setWeapon(std::make_unique<Weapon>(*weapon));
                    game[pos2].reset();
                    gotodir(player->getTargetDirection(pos2));
                }
                break;
            }
        case ObjectType::ELMAGIC:
            {
                ELmagic* elmagic = dynamic_cast<ELmagic*>(obj);
                if (elmagic) {
                    player->setWeapon(std::make_unique<ELmagic>(*elmagic));
                    game[pos2].reset();
                    gotodir(player->getTargetDirection(pos2));
                }
                break;
            }
            
        case ObjectType::ELWEAPON: 
            {
                ELweapon* elweapon = dynamic_cast<ELweapon*>(obj);
                if (elweapon) {
                    player->setWeapon(std::make_unique<ELweapon>(*elweapon));
                    game[pos2].reset();
                    gotodir(player->getTargetDirection(pos2));
                }
                break;
            }
        case ObjectType::GOLD:
            {
                Gold* gold = dynamic_cast<Gold*>(obj);
                if (gold){
                    _STATUS.addGold(gold->getAmount());
                    _STATUS.addXp(gold->getAmount());
                    game[pos2].reset();
                    gotodir(player->getTargetDirection(pos2));
                }
                

                break;
            }
        case ObjectType::RUBY:
            {
                Ruby* ruby = dynamic_cast<Ruby*>(obj);
                if (ruby){
                    _STATUS.addGold(ruby->getAmount() * 2);
                    _STATUS.addXp(ruby->getAmount() * 5);
                    game[pos2].reset();
                    gotodir(player->getTargetDirection(pos2));
                }
                

                break;
            }
        case ObjectType::THORN:
            {
            Thorn* thorn = dynamic_cast<Thorn*>(obj);
                if (thorn){
                    if (thorn->getDirections()[thorn->getTargetDirection(pos1)]){
                        player->takeDamage(thorn->getAmount(), DamageType::NORMAL);
                    }
                    game[pos2].reset();
                    gotodir(player->getTargetDirection(pos2));
                }
                break;
            }
        case ObjectType::GUN:
            {
                Gun* gun = dynamic_cast<Gun*>(obj);
                if (gun){
                    auto directions = gun->getDirections();
                    for (int i = 0; i < 4; i++){
                        int targetpos = gun->getTargetPosition(i);
                        if (directions[i]){
                            if(0 <= targetpos && targetpos < 9 && game[targetpos]){
                                game[targetpos]->takeDamage(gun->getAmount(), DamageType::FIRE);
                            }
                            
                        }
                    }
                    game[pos2].reset();
                    gotodir(player->getTargetDirection(pos2));
                }
                
                break;
            }
        case ObjectType::OBJECT:
            {
                game[pos2].reset();
                gotodir(player->getTargetDirection(pos2));
                break;
            }
        case ObjectType::POTION:
        {
            Potion* pot = dynamic_cast<Potion*>(obj);
            if (pot){
                switch(pot->getPotionType()){
                case PotionType::HEAL:
                    {
                        int hp = player->getHP() + pot->getPower();
                        int maxhp = player-> getMaxHP();
                        player->setHP(hp < maxhp ? hp : maxhp);
                        game[pos2].reset();
                        gotodir(player->getTargetDirection(pos2));
                        break;
                    }
                case PotionType::POISON:
                    {
                        int hp = player->getHP() - pot->getPower();
                        player->setHP(hp);
                        game[pos2].reset();
                        gotodir(player->getTargetDirection(pos2));
                        break;
                    }
                default: 
                    {
                        game[pos2].reset();
                        std::cerr << "Unknown PotionType in handleIMMEDIATE_PASS: "
                                  << static_cast<int>(obj->returntype())
                                  << std::endl;
                        break;
                    }

                }
            }

            break;
            
        }
        default: {
            std::cerr << "Unknown ObjectType in handleIMMEDIATE_PASS: "
                      << static_cast<int>(obj->returntype())
                      << std::endl;
            break;
        }
    }
}

void Game::handleSWAP_REQUIRED(int pos1, int pos2){ 
    if (pos1 != player->getPosition()) return;
    Object* obj = game[pos2].get();
    if (!obj) {
        std::cerr << "ERROR: Null object at position " << pos2 << std::endl;
        return;
    }
    switch (obj->returntype()){
        case ObjectType::BOMB:
        case ObjectType::DYNAMITE:
            switchcards(pos1, pos2);
            break;
        default:
            std::cerr << "Unknown ObjectType in handleSWAP_REQUIRED: "
                      << static_cast<int>(obj->returntype())
                      << std::endl;
            break;
            

    }
    
}

void Game::handleTRIGGER_ON_STAY(int pos1){ 
    Object* obj = game[pos1].get();
    if (!obj) {
        std::cerr << "ERROR: Null object at position " << pos1 << std::endl;
        return;
    }
    switch (obj->returntype()){
        case ObjectType::CHEST:{
            Chest* chest = dynamic_cast<Chest*>(obj);
            std::unique_ptr<Object> loot = chest->generateLoot(_STATUS);
            loot->setPosition(pos1);
            loot->setOnDamageCallback([this](int pos, DamageType type) {
                this->handleObjectDamage(pos, type);
            });
            game[pos1] = std::move(loot);
            break;
        }
            
        default:
            std::cerr << "Unknown ObjectType in handleTRIGGER_ON_STAY: "
                      << static_cast<int>(obj->returntype())
                      << std::endl;
            break;
    }

}

// Handles combat with enemies
void Game::handleCOMBAT_DEPENDENT(int pos1, int pos2){
    if (pos1 != player->getPosition()) return;
    Object* obj = game[pos2].get();
    if (!obj) {
        std::cerr << "ERROR: Null object at position " << pos2 << std::endl;
        return;
    }
    switch (obj->returntype()){
        case ObjectType::ENEMY:
        case ObjectType::BAT:
        case ObjectType::MAG:
        case ObjectType::ELEMENTAL:
            {
                Enemy* enemy = dynamic_cast<Enemy*>(obj);
                if (enemy){
                    int enemyHP = enemy->getHP();
                    Weapon* playerWeapon = player->getWeapon();
                    if (!playerWeapon){
                        player->takeDamage(enemyHP, DamageType::NORMAL);
                        game[pos2].reset();
                        gotodir(player->getTargetDirection(pos2));
                    }else{
                        int initialWeaponDmg = playerWeapon->getDamage();
                        enemy->takeDamage(playerWeapon);
                        _STATUS.addXp(std::max(initialWeaponDmg - playerWeapon->getDamage(), 0));
                        if (playerWeapon->returntype() == ObjectType::ELMAGIC){
                            int pos3 = game[pos2]->getTargetPosition(player->getTargetDirection(pos2));
                            if (pos3 >= 0 && pos3 < 9 ){
                                game[pos3]->takeDamage(initialWeaponDmg - playerWeapon->getDamage(), playerWeapon->getElement());
                            }
                        }

                        if (playerWeapon->getDamage() <= 0) {
                            player->removeWeapon();
                        }
                    }
                    break;
                }
            }
            
        default:
            std::cerr << "Unknown ObjectType in handleCOMBAT_DEPENDENT: "
                      << static_cast<int>(obj->returntype())
                      << std::endl;
            break;
    }

}

bool Game::isPlayerAlive() const {
    return player && player->getHP() > 0;
}

// Initialize damage callbacks for all objects
void Game::initializeDamageCallbacks() {
    for (auto& obj : game) {
        if (obj) {
            obj->setOnDamageCallback([this](int pos, DamageType type) {
                this->handleObjectDamage(pos, type);
            });
        }
    }
    
    if (player) {
        player->setOnDamageCallback([this](int pos, DamageType type) {
            this->handleObjectDamage(pos, type);
        });
    }
}

// Handle damage events and object death
void Game::handleObjectDamage(int pos, DamageType type) {
    if (pos < 0 || pos >= 9 || !game[pos]) {
        std::cerr << "Invalid position in handleObjectDamage: " << pos << std::endl;
        return;
    }
    
    Object* obj = game[pos].get();
    
    if (auto* character = dynamic_cast<Character*>(obj)) {
        if (character->getHP() <= 0) {
            handleObjectDeath(pos);
        }
        return;
    }
    if (auto* weapon = dynamic_cast<Weapon*>(obj)) {
        if (weapon->getDamage() <= 0) {
            handleObjectDeath(pos);
        }
        return;
    }
    if (auto* thornOrGun = dynamic_cast<Thorn*>(obj)) {
        if (thornOrGun->getAmount() <= 0) {
            handleObjectDeath(pos);
        }
        return;
    }
    if (auto* pot = dynamic_cast<Potion*>(obj)) {
        if (pot->getPower() <= 0) {
            handleObjectDeath(pos);
        }
        return;
    }
    if (auto* gold = dynamic_cast<Gold*>(obj)) {
        if (gold->getAmount() <= 0) {
            handleObjectDeath(pos);
        }
        return;
    }
    if (auto* bomb = dynamic_cast<Bomb*>(obj)) {
        if (bomb->getDuration() <= 0 || bomb -> getAmount() <= 0) {
            handleObjectDeath(pos);
        }
        return;
    }
    

}

// Handle object death and replacement
void Game::handleObjectDeath(int pos) {
    if (pos < 0 || pos >= 9) {
        std::cerr << "Invalid position in handleObjectDeath: " << pos << std::endl;
        return;
    }
    if (game[pos].get() == player) {
        gameOver = true;
        return;
    }
    Object* deadObj = game[pos].get();
    if (!deadObj) return;
    
    ObjectType type = deadObj->returntype();

    switch (type) {
        case ObjectType::BOMB:
            {
                Bomb* bomb = dynamic_cast<Bomb*>(deadObj);
                if (bomb){
                    int bombAmount = bomb->getAmount();
                    std::vector<int> targetPositions;
                    for (int i = 0; i < 4; i++){
                        targetPositions.push_back(bomb->getTargetPosition(i));
                    }
                    
                    game[pos] = std::make_unique<Gold>(pos, 100);
                    
                    for (int i = 0; i < 4; i++){
                        int targetpos = targetPositions[i];
                        if(0 <= targetpos && targetpos < 9 && game[targetpos]){
                            game[targetpos]->takeDamage(bombAmount, DamageType::NORMAL);
                        }
                    }
                }
                break;
            }
        case ObjectType::DYNAMITE:
            {
                Dynamite* dynamite = dynamic_cast<Dynamite*>(deadObj);
                if (dynamite){
                    int dynamiteAmount = dynamite->getAmount();
                    int row = pos / 3;
                    
                    game[pos] = std::make_unique<Gold>(pos, 100);
                    
                    for (int i = 0; i < 3; i++){
                        int targetpos = row * 3 + i;
                        if(0 <= targetpos && targetpos < 9 && game[targetpos] && pos != targetpos){
                            game[targetpos]->takeDamage(dynamiteAmount, DamageType::NORMAL);
                        }
                    }
                }
                break;
            }
        case ObjectType::BAT:
            {
                game[pos] = std::make_unique<Potion>(pos, rand() % 15 + 3, PotionType::HEAL);
                _STATUS.addXp(10);
                break;
            }
        case ObjectType::GUN:
        case ObjectType::THORN:
            game[pos] = std::make_unique<Object>(pos);
            break;
        case ObjectType::WEAPON:
        case ObjectType::RUBY:
        case ObjectType::ELWEAPON:
            game[pos] = std::make_unique<Gold>(pos, 10 + rand() % 20);
            break;
        case ObjectType::ENEMY:
        case ObjectType::ELEMENTAL:
        case ObjectType::MAG:
            _STATUS.addXp(20);
            game[pos] = std::make_unique<Gold>(pos, 10 + rand() % 20);
            break;
        case ObjectType::GOLD:
            game[pos] = std::make_unique<Object>(pos);
            break;

        default:
            game[pos] = std::make_unique<Object>(pos);
            break;
    }
    
    if (game[pos]) {
        game[pos]->setOnDamageCallback([this](int pos, DamageType type) {
            this->handleObjectDamage(pos, type);
        });
    }
}
