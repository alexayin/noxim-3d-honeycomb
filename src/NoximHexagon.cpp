/*
 * File:   NoximHexagon.cpp
 * Author: nan
 *
 * Created on 06 March 2011, 20:03
 */
#include <unistd.h>

#include "NoximHexagon.h"


void NoximHexagon::buildHexagonTree(int meshSize)
{
    unsigned short level = 1;
    NoximHexagon* rootHexagon = new NoximHexagon(level, "Root");

    std::cout << "------------buildHexagonTree-------------: meshSize = " << meshSize << std::endl;
    // queue for level-order creation
    Queue queue = Queue_CreateQueue(100);
    std::cout << "Queue for level order creation initilized" << std::endl;
    std::cout << "Empty? " << Queue_IsEmpty(queue) << ", isFull? " << Queue_IsFull(queue) << std::endl;
    Queue_Enqueue(rootHexagon, queue);

    // statistics
    unsigned int levelCount =  1;
    unsigned int count = 0;
    unsigned short currentLevel = 0;

    while(!Queue_IsEmpty(queue))
    {
        NoximHexagon* h = (NoximHexagon*) Queue_FrontAndDequeue(queue);
        // create next-level neighbors
        if (h && h->getLevel() < meshSize)
        {
            // statistics
            if(h->getLevel()>currentLevel)
            {
                currentLevel =  h->getLevel();
                count +=levelCount;
                std::cout << levelCount << " hexagons for level: " << currentLevel << " (total: " << count << ") created." << std::endl;
                levelCount = 0;
            }
            const bool n0Created = h->n0 != NULL;
            const bool n1Created = h->n1 != NULL;
            const bool n2Created = h->n2 != NULL;
            const bool n3Created = h->n3 != NULL;
            const bool n4Created = h->n4 != NULL;
            const bool n5Created = h->n5 != NULL;

            if (!n0Created)
            {
                h->n0 = h->createNeighbor("n0");
                levelCount++;
                Queue_Enqueue(h->n0, queue);
            }
            h->n0->n3 = h;

            if (!n1Created)
            {
                h->n1 = h->createNeighbor("n1");
                levelCount++;
                Queue_Enqueue(h->n1, queue);
            }
            h->n1->n4 = h;
            h->n0->n2 = h->n1;
            h->n1->n5 = h->n0;

            if (!n2Created)
            {
                h->n2 = h->createNeighbor("n2");
                levelCount++;
                Queue_Enqueue(h->n2, queue);
            }
            h->n2->n5 = h;
            h->n1->n3 = h->n2;
            h->n2->n0 = h->n1;

            if (!n3Created)
            {
                h->n3 = h->createNeighbor("n3");
                levelCount++;
                Queue_Enqueue(h->n3, queue);
            }
            h->n3->n0 = h;
            h->n2->n4 = h->n3;
            h->n3->n1 = h->n2;

            if (!n4Created)
            {
                h->n4 = h->createNeighbor("n4");
                levelCount++;
                Queue_Enqueue(h->n4, queue);
            }
            h->n4->n1 = h;
            h->n3->n5 = h->n4;
            h->n4->n2 = h->n3;

            if (!n5Created)
            {
                h->n5 = h->createNeighbor("n5");
                levelCount++;
                Queue_Enqueue(h->n5, queue);
            }
            h->n5->n2 = h;
            h->n4->n0 = h->n5;
            h->n5->n3 = h->n4;

            // relationships between n5 and n0
            h->n5->n1 = h->n0;
            h->n0->n4 = h->n5;
        }
    }
    count +=levelCount;
    std::cout << levelCount << " hexagons for level: " << currentLevel << " (total: " << count << ") created." << std::endl;

}

NoximHexagon* NoximHexagon::createNeighbor(string name)
{
    NoximHexagon* n = new NoximHexagon(level + 1, name);
    n->setCreator(this);
    cout << "Neighbour: [" << n->toString() << "] created" << endl;
    //usleep(1000000);
    //guiManager->createHexagon(level);
    return n;
}

string NoximHexagon::toString()
{
    string ret = getName();
    if(getCreator())
    {
        ret += " <= " + getCreator()->toString();
    }
    return ret;
}

void NoximHexagon::setCreator(NoximHexagon* creator)
{
    this->creator = creator;
}

NoximHexagon* NoximHexagon::getCreator() const
{
    return creator;
}

void NoximHexagon::setName(string name)
{
    this->name = name;
}

string NoximHexagon::getName() const
{
    return name;
}

unsigned short NoximHexagon::getLevel() const
{
    return level;
}

void NoximHexagon::setLevel(unsigned short level)
{
    this->level = level;
}


NoximHexagon::NoximHexagon(const NoximHexagon& orig)
{
}

NoximHexagon::~NoximHexagon()
{
}

