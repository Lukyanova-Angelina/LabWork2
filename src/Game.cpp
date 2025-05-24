#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <chrono>
#include <thread>

Game::Game(){
    generate_game();
}

// Генерация игры
void Game::generate_game() {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < 9; ++i) {
        if (i == 4) {
            game[i] = std::make_unique<Player>(i, "Hero", 100, 100);
            player = static_cast<Player*>(game[i].get());
        } else {
            generatecard(i);
        }
    }
    clean();
    draw();
}

// Обновление игры
void Game::update() {
    Steps++;
    for (auto& obj : game) {
        if (obj) {
            obj->update();
        }
    }
}

// Отрисовка игры
void Game::draw() {
    const std::string EMPTY_LINE = std::string(CELL_WIDTH, ' ');
    const std::string HORIZONTAL_BORDER = "━━━━━━━━━━━━━━━━━━━━━━━━";

    for (int row = 0; row < 3; ++row) {
        std::vector<DisplayInfo> cells;
        for (int col = 0; col < 3; ++col) {
            int index = row * 3 + col;
            cells.push_back(game[index] ? game[index]->print() 
                                        : DisplayInfo{"Empty", "", "", Color::MAGENTA});
        }
        // Вывод содержимого ячеек
        for (const auto& cell : cells) {
            std::cout << cell.color << "┏" << HORIZONTAL_BORDER << "┓" << Color::RESET << "   ";
        }
        std::cout << "\n";
        for (int line = 0; line < LINES_PER_CELL; ++line) {
            for (const auto& cell : cells) {
                std::string content;
                std::string gr = "┃";
                switch(line) {
                    case 0: content = centerText(cell.header, CELL_WIDTH); break;
                    case 2: content = centerText(cell.status, CELL_WIDTH); break;
                    case 4: content = centerText(cell.details, CELL_WIDTH); break;
                    default: content = EMPTY_LINE; 
                }

                std::cout << cell.color<<"┃" << content << "┃   "<< Color::RESET ;

            }

            std::cout << "\n";
            for (const auto& cell : cells) {
                std::cout << cell.color << "┃" <<EMPTY_LINE << "┃" << Color::RESET << "   ";
            }
            std::cout << "\n";
        }
        for (const auto& cell : cells) {
            std::cout << cell.color << "┗" << HORIZONTAL_BORDER << "┛" << Color::RESET << "   ";
        }
        std::cout << "\n\n";
        
    }
    std::cout<<Steps;
    //std::cout << "\033[41H";
}
void Game::drawcard(int pos1, int pos2, int col, int row){
    const std::string HORIZONTAL_BORDER = "━━━━━━━━━━━━━━━━━━━━━━━━";
    DisplayInfo cell = game[pos1]->print();
    std::cout.flush();
    int line = 0;
    std::cout << "\033["<<row<<";"<<col<<"H";
    std::cout << cell.color << "┏" << HORIZONTAL_BORDER << "┓" << Color::RESET << "   "<<std::flush;
    for (; line < LINES_PER_CELL; ++line) {
        std::cout.flush();
        std::string content;
        std::string gr = "┃";
        switch(line) {
            case 0: content = centerText(cell.header, CELL_WIDTH); break;
            case 2: content = centerText(cell.status, CELL_WIDTH); break;
            case 4: content = centerText(cell.details, CELL_WIDTH); break;
            default: content = std::string(CELL_WIDTH,' '); 
        }
        std::cout << "\033["<<row+line*2+1<<";"<<col<<"H";
        std::cout << cell.color<<"┃" << content << "┃   "<< Color::RESET<<std::flush;
        std::cout << "\033["<<row+line*2 + 2<<";"<<col<<"H";
        std::cout << cell.color << "┃" <<std::string(CELL_WIDTH,' ') << "┃" << Color::RESET << "   "<<std::flush;
        std::cout << "\033[41;1H" << std::flush;
    }
    std::cout << "\033["<<row+line*2 +1<<";"<<col<<"H";
    std::cout << cell.color << "┗" << HORIZONTAL_BORDER << "┛" << Color::RESET << "   "<<std::flush;
    std::cout << "\033[41;1H" << std::flush;
}
void Game::drawANIMATION(int pos1, int pos2){
    const std::string HORIZONTAL_BORDER = "━━━━━━━━━━━━━━━━━━━━━━━━";
    std::cout.flush();
    int col1 = (pos1%3)*29 + 1;
    int row1 = (pos1 / 3) * 13 + 1;
    int col2 = (pos2%3)*29 + 1;
    int row2 = (pos2 / 3) * 13 + 1;
    if (abs(pos1 - pos2) == 1){
        for (int movement = 0; movement < abs(col1 - col2) + 1; movement++){
            for (int line = 0; line < 12;++line){
                std::cout << "\033["<<row1 + line<<";"<<col1<<"H";
                std::cout << std::string(CELL_WIDTH+2,' ')<<std::flush;
                std::cout << "\033[41;1H" << std::flush;
                std::cout << "\033["<<row2 + line<<";"<<col2 - 3<<"H";
                std::cout << std::string(CELL_WIDTH+5, ' ')<<std::flush;
                std::cout << "\033[41;1H" << std::flush;
            }
            drawcard(pos1, pos2, col1 - ((col1 > col2) - (col1 < col2)) * movement,row1);
            std::cout << "\033[41;1H" << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(25));
        }
    }else{
        for (int movement = 0; movement < abs(row1 - row2) + 1; movement++){
            for (int line = 0; line < 13;++line){
                std::cout << "\033["<<row1 + line<<";"<<col1<<"H";
                std::cout << std::string(CELL_WIDTH+2,' ')<<std::flush;
                std::cout << "\033[41;1H" << std::flush;
                std::cout << "\033["<<row2 + line<<";"<<col2<<"H";
                std::cout << std::string(CELL_WIDTH+2, ' ')<<std::flush;
                std::cout << "\033[41;1H" << std::flush;
            }
            drawcard(pos1, pos2,col1,row1 - ((row1 > row2) - (row1 < row2)) * movement);
            std::cout << "\033[41;1H" << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(40));
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "\033[41;1H" << std::flush;
}
void Game::clean(){
    std::cout << "\033[2J\033[1;1H"; 
}
void Game::handleInput(char input) {// если возможность ходить есть(невыход за пределы карты), но мы можем атаковать или открыть сундук или тд тп, тогда мы не ходим, а изменяем как-то характеристики с помощью методов обькектов
    std::map<char, int> directionMap = {{'w', 0}, {'d', 1}, {'s', 2}, {'a', 3}};
    auto it = directionMap.find(input);
    if (it != directionMap.end()) {
        // Если ввод найден, проверяем возможность движения и двигаемся
        int direction = it->second;
        if (player->possibletomove(direction)) { // есть возможность ходить, =>  дальше делаем проверку на карту, если это золото/оружие/или у игрока нет оружие и это злодей/ловушка- идем и обрабатываем ход
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
                    handleCOMBAT_DEPENDENT(poswheremove);
                    break;
            }
            
            //gotodir(player->getTargetDirection(poswheremove));
            //switchcards(playerpos, poswheremove);
            update();
        }
    } else {
        std::cout << "Неизвестная клавиша: " << input << std::endl;
    }
}
void Game::switchcards(int pos1, int pos2){ // меняем местами карточки
    std::unique_ptr<Object> temp = std::move(game[pos2]);
    game[pos2] = std::move(game[pos1]);
    game[pos1] = std::move(temp);
    game[pos1]->setPosition(pos1);
    game[pos2]->setPosition(pos2);
}

void Game::movecard(int pos, int direction){ // изменяем позицию карточки
    drawANIMATION(pos, game[pos]->getTargetPosition(direction));
    game[pos]->move(direction);

    game[game[pos]->getPosition()] = std::move(game[pos]);

}
void Game::gotodir(int direction){ // перемещаем карточку (с генерацией)
    if (player->possibletomove((direction+2)%4)){// если герой может двинуться в противоположную сторону
        int temp = player->getTargetPosition((direction+2)%4);
        movecard(player->getPosition(), direction);
        movecard(temp, direction);
        generatecard(temp);

    }else{
        if (player->possibletomove((direction+1)%4)){ // по часовой
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
void Game::generatecard(int pos) { // пока что так, дальше придумать систему генерации
    int randomValue = rand() % 100;
    if (randomValue < 50) {
        game[pos] = std::make_unique<ELmagic>(pos, 1);
    } else if (randomValue < 70){
        game[pos] = std::make_unique<Weapon>(pos);
    }else{
        game[pos] = std::make_unique<ELweapon>(pos, 0);
    }
}
void Game::handleIMMEDIATE_PASS(int pos1, int pos2) { // если это ловушки, лут, зелья или оружие, просто ходим
    if (pos1 != player->getPosition()) return;
    Object* obj = game[pos2].get();
    if (!obj) return;
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
        case ObjectType::RUBY:
        case ObjectType::THORN:
        case ObjectType::GUN:
        case ObjectType::BOMB:
        case ObjectType::DYNAMITE:
        case ObjectType::POISON:
        case ObjectType::FASTHEAL:
        case ObjectType::TIMEHEAL: {
            std::cout << "Данный тип пока не реализован" << std::endl;
            break;
        }
        default: {
            std::cerr << "Неподдерживаемый тип объекта: "
                      << static_cast<int>(obj->returntype())
                      << std::endl;
            break;
        }
    }
}
void Game::handleSWAP_REQUIRED(int pos1, int pos2){ // если можно поменять карточки местами
    //switchcards(pos1, pos2);
}
void Game::handleTRIGGER_ON_STAY(int pos1){ // если сундук, то стоим на месте

}
void Game::handleCOMBAT_DEPENDENT(int pos1){

}