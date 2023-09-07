#include "StudentWorld.h"

#include <string>
#include <stack>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
    
	return new StudentWorld(assetDir);
    
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp


StudentWorld::StudentWorld(string assetDir)
 : GameWorld(assetDir), m_TunnelMan(nullptr)
{
    
    m_TunnelMan = NULL;
       for (int y = 0; y < 64; ++y) {
           for (int x = 0; x < 64; ++x) {
               if(x == 30 || x == 31 || x == 32 || x == 33) //mineshaft
                   continue;
               m_Earth[x][y] = NULL;
           }
       }
}

StudentWorld::~StudentWorld(){

}


TunnelMan* StudentWorld::getTunnelMan(){
    return m_TunnelMan;
}

void StudentWorld::setDisplayText(){
    int gold = m_TunnelMan->getNugget();
    int score = getScore();
    int lives = getLives();
    int lvl = getLevel();
    int sqrt = m_TunnelMan->getSquirt();
    int sonar = m_TunnelMan->getSonar();
    int health = m_TunnelMan->getHealth()*10;
    int oil = getOilLeft();
    string s = "Lvl: " + std::to_string(lvl) + " Lives: " + std::to_string(lives) + " Health: " + std::to_string(health) + "% Water: " + std::to_string(sqrt) + " Gold: " + std::to_string(gold) + " Oil Left: " + std::to_string(oil) + " Sonar: " + std::to_string(sonar) + " Scr: " + std::to_string(score);
    setGameStatText(s);
}

int StudentWorld::init(){
    RegProt* regularP = new RegProt(getLevel());
    regularP->setWorld(this);
    m_goodies.push_back(regularP);
    m_TunnelMan = new TunnelMan;
    m_TunnelMan->setWorld(this);
    //earth
    for (int y = 0; y < 60; ++y) {
        for (int x = 0; x < 64; ++x) {
            if(x == 30 & y > 3|| x == 31 & y > 3|| x == 32 & y > 3 || x == 33 & y > 3) //mineshaft
                continue;
            m_Earth[x][y] = new Earth(TID_EARTH, x, y);
            m_Earth[x][y]->setWorld(this);
        }
    }
    
    
 
    for (int i = 0; i < 15; ++i) {
        Nugget* newNugget = new Nugget;
        newNugget->setWorld(this);
        bool shouldAddNugget = true;

        if ((newNugget->getX() >= 26 && newNugget->getX() <= 33) && newNugget->getY() > 3) {
            shouldAddNugget = false;
            delete newNugget;
            newNugget = nullptr;
        } else {
            // Check for overlapping with existing goodies
            for (Goodies* existingGoodie : m_goodies) {
                int existingX = existingGoodie->getX();
                int existingY = existingGoodie->getY();

                // Check if the bottom left corner of the 4x4 space of the new nugget overlaps with the existing goodie
                if (newNugget->getX() + 3 >= existingX && newNugget->getX() <= existingX + 3 &&
                    newNugget->getY() <= existingY + 3 && newNugget->getY() + 3 >= existingY) {
                    shouldAddNugget = false;
                    delete newNugget;
                    newNugget = nullptr;
                    break;
                }
            }

            if (shouldAddNugget) {
                m_goodies.push_back(newNugget);
            }
        }
    }
    
    
    for (int i = 0; i < 5; ++i) {
        Water* newWater = new Water;
        newWater->setWorld(this);
        int level = getLevel();
        int T = std::max(100, 300 - 10*level);
        newWater->setT(T);
        bool shouldAddWater = true;

        if ((newWater->getX() >= 26 && newWater->getX() <= 33) && newWater->getY() > 3) {
            shouldAddWater = false;
            delete newWater;
            newWater = nullptr;
        } else {
            // Check for overlapping with existing goodies
            for (Goodies* existingGoodie : m_goodies) {
                int existingX = existingGoodie->getX();
                int existingY = existingGoodie->getY();

                // Check if the bottom left corner of the 4x4 space of the new nugget overlaps with the existing goodie
                if (newWater->getX() + 3 >= existingX && newWater->getX() <= existingX + 3 &&
                    newWater->getY() <= existingY + 3 && newWater->getY() + 3 >= existingY) {
                    shouldAddWater = false;
                    delete newWater;
                    newWater = nullptr;
                    break;
                }
            }

            if (shouldAddWater) {
                m_goodies.push_back(newWater);
            }
        }
    }
    
    
    
    
    Sonar* sonar = new Sonar;
    sonar->setWorld(this);
    int level = getLevel();
    int T = std::max(100, 300 - 10*level);
    sonar->setTicks(T);
    m_goodies.push_back(sonar);
    

    //boulders
    
    for (int i = 0; i < 5; i++) {
        int x, y;
        bool overlap = false;
        do {
            x = rand() % 60;
            y = rand() % 56;

        } while (((x >= 26 && x <= 33) && (y >= 4 && y <= 59))); // Avoid mineshaft and overlap
        // Check for overlap with existing goodies
            for (Goodies* existingGoodie : m_goodies) {
                int xBottomLeft = existingGoodie->getX();
                int yBottomLeft = existingGoodie->getY();
                if (x + 3 >= xBottomLeft && x <= xBottomLeft + 3 &&
                    y <= yBottomLeft + 3 && y + 3 >= yBottomLeft) {
                    overlap = true;
                    break;
                }
            }
        // Create and add the boulder to the world if no overlap
        if (!overlap) {
            m_goodies.push_back(new Boulder(x, y));
            m_goodies.back()->setWorld(this);
            // Clear Earth around the Boulder
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    int xe = x + i;
                    int ye = y + j;
                    if (m_Earth[xe][ye] != nullptr) {
                        delete m_Earth[xe][ye];
                        m_Earth[xe][ye] = nullptr;
                    }
                }
            }
        }
    }
    
    
    
    for (int i = 0; i < 4; ++i) {
        Barrel* newBarrel = new Barrel;
        newBarrel->setWorld(this);
        newBarrel->setVisible(false);//TRUE FOR TESTING 
        bool shouldAddBarrel = true;

        if ((newBarrel->getX() >= 26 && newBarrel->getX() <= 33) && newBarrel->getY() > 3) {
            shouldAddBarrel = false;
            delete newBarrel;
            newBarrel = nullptr;
        } else {
            // Check for overlapping with existing goodies
            for (Goodies* existingGoodie : m_goodies) {
                int existingX = existingGoodie->getX();
                int existingY = existingGoodie->getY();

                // Check if the bottom left corner of the 4x4 space of the new barrel overlaps with the existing goodie
                if (newBarrel->getX() + 3 >= existingX && newBarrel->getX() <= existingX + 3 &&
                    newBarrel->getY() <= existingY + 3 && newBarrel->getY() + 3 >= existingY) {
                    shouldAddBarrel = false;
                    delete newBarrel;
                    newBarrel = nullptr;
                    break;
                }
            }

            if (shouldAddBarrel) {
                m_goodies.push_back(newBarrel);
            }
        }
    }
    

    return GWSTATUS_CONTINUE_GAME;
}



int StudentWorld::move(){
    setDisplayText();
    m_TunnelMan->doSomething();
    if(m_TunnelMan->getLostLife() == true){
        decLives();
        m_TunnelMan->setLostLife(false);
        return GWSTATUS_PLAYER_DIED;
    }
    
    
    if(getOilLeft() == 0){
        return GWSTATUS_FINISHED_LEVEL;
    }
    
    
        
    if(m_TunnelMan != nullptr)
    {
//        for(int i = 0; i < 15; i++){
//            if(m_goodies[i] != nullptr) //&& !m_goodies.empty())
//                m_goodies[i]->doSomething();
//
//        }
        for (int i = 0; i < m_goodies.size(); i++) {
            if (m_goodies[i] != nullptr) {
                m_goodies[i]->doSomething();
            }
        }
            
    }
    int scount = 0;
    int wcount = 0;
    std::vector<int> squirtIndicesToDelete;
    for (int i = 0; i < m_goodies.size(); ++i) {
        Nugget* nugget = dynamic_cast<Nugget*>(m_goodies[i]);
        if (nugget != nullptr && nugget->getState() == false) {
            nugget->setVisible(false);
        }
        Squirt* squirt = dynamic_cast<Squirt*>(m_goodies[i]);
        if (squirt != nullptr && squirt->getState() == false) {
            squirt->setVisible(false);
        }
        Boulder* boulder = dynamic_cast<Boulder*>(m_goodies[i]);
        if (boulder != nullptr && boulder->getStability() == "dead") {
            boulder->setVisible(false);
        }
        Barrel* barrel = dynamic_cast<Barrel*>(m_goodies[i]);
        if (barrel != nullptr && barrel->getState() == false) {
            barrel->setVisible(false);
        }
        Sonar* sonar = dynamic_cast<Sonar*>(m_goodies[i]);
        if (sonar != nullptr && sonar->getState() == true) {
            scount++;
        }
        Water* water = dynamic_cast<Water*>(m_goodies[i]);
        if (water != nullptr && water->getState() == true) {
            wcount++;
        }
        Protestor* prot = dynamic_cast<Protestor*>(m_goodies[i]);
        if (prot != nullptr && prot->getState() == true) {
            for (int j = 0; j < m_goodies.size(); ++j) {  // Use a different variable name for the loop variable
                Squirt* squirt = dynamic_cast<Squirt*>(m_goodies[j]);  // Calculate squirt pointer here
                if (squirt != nullptr) {
                    int x = prot->getX();
                    int y = prot->getY();
                    int mx = squirt->getX();
                    int my = squirt->getY();
                    int dist = sqrt(pow(x - mx, 2) + pow(y - my, 2));
                    if (dist <= 4) {
                        prot->stunned();
                        prot->annoyed(2);
                        squirtIndicesToDelete.push_back(j);

                    }
                }
            }
            for (int j = 0; j < m_goodies.size(); ++j) {  // Use a different variable name for the loop variable
                Boulder* boulder = dynamic_cast<Boulder*>(m_goodies[j]);  // Calculate boulder pointer here
                if (boulder != nullptr && boulder->getStability() == "waiting") {
                    int x = prot->getX();
                    int y = prot->getY();
                    int mx = boulder->getX();  // Use boulder instead of squirt here
                    int my = boulder->getY();  // Use boulder instead of squirt here
                    int dist = sqrt(pow(x - mx, 2) + pow(y - my, 2));
                    if (dist <= 4) {
                        prot->annoyed(100);
                    }
                }
            }
            for (int j = 0; j < m_goodies.size(); ++j) {  // Use a different variable name for the loop variable
                Nugget* nugget = dynamic_cast<Nugget*>(m_goodies[j]);  // Calculate boulder pointer here
                if (nugget != nullptr && nugget->isWaiting()) {
                    int x = prot->getX();
                    int y = prot->getY();
                    int mx = nugget->getX();  // Use boulder instead of squirt here
                    int my = nugget->getY();  // Use boulder instead of squirt here
                    int dist = sqrt(pow(x - mx, 2) + pow(y - my, 2));
                    if (dist <= 4) {
                        prot->Bribed();
                        nugget->setWaiting(false);
                        nugget->setState(false);
                    }
                }
            }
        }
       // int dist = sqrt(pow(x - mx, 2) + pow(y - my, 2));
    }
    for (int index : squirtIndicesToDelete) {
        delete m_goodies[index];
        m_goodies.erase(m_goodies.begin() + index);
    }
    int pcount = 0;
    for (int i = 0; i < m_goodies.size(); ++i) {
        Protestor* prot = dynamic_cast<Protestor*>(m_goodies[i]);
        if (prot != nullptr && prot->getState() == true) {
            pcount++;
        }
    }
    if(pcount == 0){
        int r = rand()%2;
        switch (r) {
            case 0:{
                RegProt* prot1 = new RegProt(getLevel());
                prot1->setWorld(this);
                prot1->setVisible(true);
                m_goodies.push_back(prot1);
                
                break;
            }
            case 1:{
                HardProt* prot2 = new HardProt(getLevel());
                prot2->setWorld(this);
                prot2->setVisible(true);
                m_goodies.push_back(prot2);
                break;
            }
        }

    }
    //if sonar has alrdy been collected drop a new one :-)
    if(scount == 0){
        Sonar* sonar = new Sonar;
        int level = getLevel();
        int T = std::max(100, 300 - 10*level);
        sonar->setTicks(T);
        sonar->setWorld(this);
        m_goodies.push_back(sonar);
    }
    if(wcount < 2){
        Water* newWater = new Water;
        newWater->setWorld(this);
        int level = getLevel();
        int T = std::max(100, 300 - 10*level);
        newWater->setT(T);
        m_goodies.push_back(newWater);

    }
        int x = m_TunnelMan->getX();
        int y = m_TunnelMan->getY();
        bool dug = false;
        for(int h = 0; h < 4; h++){
            for(int v = 0; v < 4; v++){
                if((x+h) < 64 && (y+h) < 64){
                    if(m_Earth[x+h][y+v] != nullptr)
                        dug = true;
                    delete m_Earth[x+h][y+v];
                    m_Earth[x+h][y+v] = nullptr;
                }
            }
        }
//    for (int i = 0; i < m_goodies.size(); ++i) {
////        Protestor* prot = dynamic_cast<Protestor*>(m_goodies[i]);
////        if (prot != nullptr && prot->getState() == false) {
////            ProtGiveUp(prot);
////            if(prot->getX() == 60 && prot->getY() == 60)
////                ProtDead();
////        }
//        if (m_goodies[i]->getVal() == "prot"){
//            if(m_goodies[i] != nullptr && m_goodies[i]->getState() == false){
//                Protestor* prot = dynamic_cast<Protestor*>(m_goodies[i]);
//                ProtGiveUp(prot);
//                if((prot->getX() == 54 || prot->getX() == 55 ||prot->getX() == 56 || prot->getX() == 57 || prot->getX() == 58 ||prot->getX() == 59 || prot->getX() == 60) && prot->getY() == 60)
//                    ProtDead();
//            }
//        }
//    }
    if(dug){
        GameWorld::playSound(SOUND_DIG);
    }
    
//    for (int i = 0; i < m_goodies.size(); ++i) {
//        Nugget* nugget = dynamic_cast<Nugget*>(m_goodies[i]);
//        if (nugget != nullptr && nugget->isWaiting() == true) {
//                nugget->setTicks(-1);            
//        }
//    }
        // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
        // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level
        //decLives();
        return GWSTATUS_CONTINUE_GAME;
    
}



void StudentWorld::cleanUp(){
    //clean up earth & Tunnelman
    if(m_TunnelMan != nullptr){
        delete m_TunnelMan;
        m_TunnelMan = nullptr;
    }
    for (int y = 0; y < 64; ++y) {
        for (int x = 0; x < 64; ++x) {
            if(m_Earth[x][y] != nullptr){
                delete m_Earth[x][y];
                m_Earth[x][y] = nullptr;
            }
        }
    }
    for (Goodies* ptr : m_goodies) {
        if(ptr != nullptr){
            delete ptr;
            ptr = nullptr;
        }
        m_goodies.clear();
    }
    
    
    
}

bool StudentWorld::isBoulderAt(int x, int y) const {
    // Check if there's a Boulder at (x, y)
//    for (const auto& goodie : m_goodies) {
//        if (goodie->getState() && dynamic_cast<Boulder*>(goodie) != nullptr && goodie->getX() == x && goodie->getY() == y) {
//            return true;
//        }
    for (int i = 0; i < m_goodies.size(); ++i) {
//        Boulder* boulder = dynamic_cast<Boulder*>(m_goodies[i]);
//        if (boulder != nullptr && boulder->getStability() != "dead" && boulder->getX() == x && boulder->getY() == y) {
//            return true;
//        }
        if(m_goodies[i] != nullptr && (m_goodies[i]->getStability() == "stable" || m_goodies[i]->getStability() == "waiting") && m_goodies[i]->getX() == x && m_goodies[i]->getY() == y) {
                        return true;
        }
    }
    return false;
}

bool StudentWorld::hasEarth(int x, int y) const {
    if (x < 0 || x >= 64 || y < 0 || y >= 64) {
        return false; // Out of bounds
    }
    return m_Earth[x][y] != nullptr;
}




void StudentWorld::addGoodie(Goodies* goodie){
    m_goodies.push_back(goodie);
}


void StudentWorld::illuminate(int x, int y){
    for (int i = 0; i < m_goodies.size(); ++i) {
        if(m_goodies[i]->getVal() == "nugget" || m_goodies[i]->getVal() == "barrel"){
            int x = m_goodies[i]->getX();
            int y = m_goodies[i]->getY();
            int dist = sqrt(pow(m_TunnelMan->getX() - x, 2) + pow(m_TunnelMan->getY() - y, 2));
            if(dist < 12.0)
                m_goodies[i]->setVisible(true);
        }
    }
}

void StudentWorld::dropNug(int x, int y){
    if(m_TunnelMan->getNugget() <= 0)
        return;
    m_TunnelMan->removeNugget();
    for (int i = 0; i < m_goodies.size(); ++i) {
        if(m_goodies[i]->getVal() == "nugget" && m_goodies[i]->isWaiting() == false && m_goodies[i]->getState() == true){
            m_goodies[i]->moveTo(x, y);
            m_goodies[i]->setVisible(true);
            m_goodies[i]->setWaiting(true);
           // m_goodies[i]->setState(true);
            break;
        }
    }
    return;
}



int StudentWorld::getOilLeft(){
    int counter = 0;
    for (int i = 0; i < m_goodies.size(); ++i) {
        if(m_goodies[i]->getVal() == "barrel" && m_goodies[i]->getState() == true){
            counter++;
        }
    }
    return counter;
}

void StudentWorld::ProtDead(){

    for (int i = 0; i < m_goodies.size(); ++i) {
        Protestor* prot = dynamic_cast<Protestor*>(m_goodies[i]);
        if (prot != nullptr) {
            //prot->setState(false);
            prot->setVisible(false);
        }
    }
}

void StudentWorld::ProtGiveUp(Protestor* prot) {
        // Perform the DFS-based pathfinding to find the next step
        for (int i = 0; i < 64; i++) {
            for (int j = 0; j < 64; j++) {
                m_dfs[i][j] = 0;
            }
        }

        int a = prot->getX();
        int b = prot->getY();

        std::stack<std::pair<int, int>> st;
        st.push(std::make_pair(60, 60));
        m_dfs[60][60] = 1;

        while (!st.empty()) {
            std::pair<int, int> c = st.top();
            st.pop();

            int x = c.first;
            int y = c.second;

            // Left
            if (validMove(x, y, GraphObject::left) && m_dfs[x - 1][y] == 0) {
                st.push(std::make_pair(x - 1, y));
                m_dfs[x - 1][y] = m_dfs[x][y] + 1;
            }
            // Right
            if (validMove(x, y, GraphObject::right) && m_dfs[x + 1][y] == 0) {
                st.push(std::make_pair(x + 1, y));
                m_dfs[x + 1][y] = m_dfs[x][y] + 1;
            }
            // Up
            if (validMove(x, y, GraphObject::up) && m_dfs[x][y + 1] == 0) {
                st.push(std::make_pair(x, y + 1));
                m_dfs[x][y + 1] = m_dfs[x][y] + 1;
            }
            // Down
            if (validMove(x, y, GraphObject::down) && m_dfs[x][y - 1] == 0) {
                st.push(std::make_pair(x, y - 1));
                m_dfs[x][y - 1] = m_dfs[x][y] + 1;
            }
        }

        // Check available moves and move one step closer
        GraphObject::Direction bestMove = GraphObject::none;
        int minDist = m_dfs[a][b];
        if (validMove(a, b, GraphObject::left) && m_dfs[a - 1][b] < minDist) {
            bestMove = GraphObject::left;
            minDist = m_dfs[a - 1][b];
        }
        if (validMove(a, b, GraphObject::right) && m_dfs[a + 1][b] < minDist) {
            bestMove = GraphObject::right;
            minDist = m_dfs[a + 1][b];
        }
        if (validMove(a, b, GraphObject::up) && m_dfs[a][b + 1] < minDist) {
            bestMove = GraphObject::up;
            minDist = m_dfs[a][b + 1];
        }
        if (validMove(a, b, GraphObject::down) && m_dfs[a][b - 1] < minDist) {
            bestMove = GraphObject::down;
        }

        // Move Protestor one step closer
        if (bestMove != GraphObject::none) {
            prot->moveD(bestMove);
        }
    }




bool StudentWorld::isBoulderWithinRange(int x, int y) {
    for (int i = -3; i <= 3; i++) {
        for (int j = -3; j <= 3; j++) {
            if (isBoulderAt(x + i, y + j)) {
                return true;
            }
        }
    }
    return false;
}

bool StudentWorld::validMove(int x, int y, GraphObject::Direction dir) {
    switch (dir) {
        case GraphObject::left:
            for (int i = x - 1; i >= x - 4; i--) {
                if (i >= 0 && (hasEarth(i, y) || isBoulderWithinRange(i, y))) {
                    return false;
                }
            }
            return true;

        case GraphObject::right:
            for (int i = x + 1; i <= x + 4; i++) {
                if (i < 64 && (hasEarth(i, y) || isBoulderWithinRange(i, y))) {
                    return false;
                }
            }
            return true;

        case GraphObject::up:
            for (int j = y + 1; j <= y + 4; j++) {
                if (j < 64 && (hasEarth(x, j) || isBoulderWithinRange(x, j))) {
                    return false;
                }
            }
            return true;

        case GraphObject::down:
            for (int j = y - 1; j >= y - 4; j--) {
                if (j >= 0 && (hasEarth(x, j) || isBoulderWithinRange(x, j))) {
                    return false;
                }
            }
            return true;

        default:
            return false;
    }
}
