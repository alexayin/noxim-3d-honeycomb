/*
 * File:   NoximHexagon.h
 * Author: nan
 *
 * Created on 06 March 2011, 20:03
 */

#ifndef NOXIMHEXAGON_H
#define	NOXIMHEXAGON_H

#include <stdlib.h>

#include <string>

#include "NoximTile.h"

extern "C" {
#include "queue.h"
}

//#include "../gui/noximguimanager.h"

using namespace std;

class NoximHexagon {

//typedef NoximHexagon ElementType;

public:
    NoximHexagon(unsigned short level, string name) {
        setLevel(level);
        setName(name);
        n0 = NULL;
        n1 = NULL;
        n2 = NULL;
        n3 = NULL;
        n4 = NULL;
        n5 = NULL;
        creator = NULL;

        //guiManager = NoximGuiManager::getInstance();
        //initilizeTiles();
    }
    NoximHexagon(const NoximHexagon& orig);
    virtual ~NoximHexagon();

    void initilizeTiles() {
        pxTile = createTile();
        mxTile = createTile();
        pyTile = createTile();
        myTile = createTile();
        pzTile = createTile();
        mzTile = createTile();
    }

    NoximTile* createTile() {
        return new NoximTile("title");
    }

    static void buildHexagonTree(int meshSize);

    NoximHexagon* createNeighbor(string name);

    string toString();

    void setCreator(NoximHexagon* creator);
    NoximHexagon* getCreator() const;
    void setName(string name);
    string getName() const;
    unsigned short getLevel() const;
    void setLevel(unsigned short level);

    // link to neighbors
    NoximHexagon* n0;
    NoximHexagon* n1;
    NoximHexagon* n2;
    NoximHexagon* n3;
    NoximHexagon* n4;
    NoximHexagon* n5;

private:
    unsigned short level;
    string name;
    // tiles as vertices
    NoximTile* pxTile;
    NoximTile* mxTile;
    NoximTile* pyTile;
    NoximTile* myTile;
    NoximTile* pzTile;
    NoximTile* mzTile;

    // link to creator
    NoximHexagon* creator;

    // GUI
    //NoximGuiManager* guiManager;

};

#endif	/* NOXIMHEXAGON_H */

