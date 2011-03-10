/*
 * Noxim - the NoC Simulator
 *
 * (C) 2005-2010 by the University of Catania
 * For the complete list of authors refer to file ../doc/AUTHORS.txt
 * For the license applied to these sources refer to file ../doc/LICENSE.txt
 *
 * This file contains the implementation of the Network-on-Chip
 */

#include "NoximHMNoC.h"

extern "C"{
#include "queue.h"
}

using namespace std;

void NoximHMNoC::buildHoneycombMesh()
{
    cout << "buildHoneycombMesh()" <<endl;
    // Check for routing table availability
    if (NoximGlobalParams::routing_algorithm == ROUTING_TABLE_BASED)
        assert(grtable.load(NoximGlobalParams::routing_table_filename));

    // Check for traffic table availability
    if (NoximGlobalParams::traffic_distribution == TRAFFIC_TABLE_BASED)
        assert(gttable.load(NoximGlobalParams::traffic_table_filename));

    // Create honeycomb mesh
    NoximHexagon* root = NoximHexagon::buildHexagonTree(NoximGlobalParams::honeycomb_mesh_size);

    // Travese (level-order) the tree
//    Queue q = Queue_CreateQueue(100);
//    Queue_Enqueue(root,q);
//    while(!Queue_IsEmpty(q))
//    {
//        NoximHexagon* h = (NoximHexagon*) Queue_FrontAndDequeue(q);
//
//    }

    // dummy NoximNoP_data structure
    NoximNoP_data tmp_NoP;

    tmp_NoP.sender_id = NOT_VALID;

    for (int i = 0; i < DIRECTIONS_HM; i++) {
        tmp_NoP.channel_status_neighbor[i].free_slots = NOT_VALID;
        tmp_NoP.channel_status_neighbor[i].available = false;
    }

    /*
    // Clear signals for borderline nodes
    for (int i = 0; i <= NoximGlobalParams::mesh_dim_x; i++) {
	req_to_south[i][0] = 0;
	ack_to_north[i][0] = 0;
	req_to_north[i][NoximGlobalParams::mesh_dim_y] = 0;
	ack_to_south[i][NoximGlobalParams::mesh_dim_y] = 0;

	free_slots_to_south[i][0].write(NOT_VALID);
	free_slots_to_north[i][NoximGlobalParams::mesh_dim_y].write(NOT_VALID);

	NoP_data_to_south[i][0].write(tmp_NoP);
	NoP_data_to_north[i][NoximGlobalParams::mesh_dim_y].write(tmp_NoP);

    }

    for (int j = 0; j <= NoximGlobalParams::mesh_dim_y; j++) {
	req_to_east[0][j] = 0;
	ack_to_west[0][j] = 0;
	req_to_west[NoximGlobalParams::mesh_dim_x][j] = 0;
	ack_to_east[NoximGlobalParams::mesh_dim_x][j] = 0;

	free_slots_to_east[0][j].write(NOT_VALID);
	free_slots_to_west[NoximGlobalParams::mesh_dim_x][j].write(NOT_VALID);

	NoP_data_to_east[0][j].write(tmp_NoP);
	NoP_data_to_west[NoximGlobalParams::mesh_dim_x][j].write(tmp_NoP);

    }

    // invalidate reservation table entries for non-exhistent channels
    for (int i = 0; i < NoximGlobalParams::mesh_dim_x; i++) {
	t[i][0]->r->reservation_table.invalidate(DIRECTION_NORTH);
	t[i][NoximGlobalParams::mesh_dim_y - 1]->r->reservation_table.invalidate(DIRECTION_SOUTH);
    }
    for (int j = 0; j < NoximGlobalParams::mesh_dim_y; j++) {
	t[0][j]->r->reservation_table.invalidate(DIRECTION_WEST);
	t[NoximGlobalParams::mesh_dim_x - 1][j]->r->reservation_table.invalidate(DIRECTION_EAST);
    }
    */
}



//NoximHMTile *NoximHMNoC::searchNode(const int id) const
//{
//    for (int i = 0; i < NoximGlobalParams::mesh_dim_x; i++)
//	for (int j = 0; j < NoximGlobalParams::mesh_dim_y; j++)
//	    if (t[i][j]->r->local_id == id)
//		return t[i][j];
//
//    return false;
//}
