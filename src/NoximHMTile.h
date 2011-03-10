/*
 * Noxim - the NoC Simulator
 *
 * (C) 2005-2010 by the University of Catania
 * For the complete list of authors refer to file ../doc/AUTHORS.txt
 * For the license applied to these sources refer to file ../doc/LICENSE.txt
 *
 * This file contains the declaration of the tile
 */

#ifndef __NOXIMHMTILE_H__
#define __NOXIMHMTILE_H__

#include <systemc.h>
#include "NoximHMRouter.h"
#include "NoximProcessingElement.h"

using namespace std;

SC_MODULE(NoximHMTile)
{

    // I/O Ports
    sc_in_clk clock;		                // The input clock for the tile
    sc_in <bool> reset;	                        // The reset signal for the tile

    sc_in <NoximFlit> flit_rx[DIRECTIONS_HM];	// The input channels
    sc_in <bool> req_rx[DIRECTIONS_HM];	        // The requests associated with the input channels
    sc_out <bool> ack_rx[DIRECTIONS_HM];	        // The outgoing ack signals associated with the input channels

    sc_out <NoximFlit> flit_tx[DIRECTIONS_HM];	// The output channels
    sc_out <bool> req_tx[DIRECTIONS_HM];	        // The requests associated with the output channels
    sc_in <bool> ack_tx[DIRECTIONS_HM];	        // The outgoing ack signals associated with the output channels

    sc_out <int> free_slots[DIRECTIONS_HM];
    sc_in <int> free_slots_neighbor[DIRECTIONS_HM];

    // NoP related I/O
    sc_out < NoximNoP_data > NoP_data_out[DIRECTIONS_HM];
    sc_in < NoximNoP_data > NoP_data_in[DIRECTIONS_HM];

    // Signals
    sc_signal <NoximFlit> flit_rx_local;	// The input channels
    sc_signal <bool> req_rx_local;              // The requests associated with the input channels
    sc_signal <bool> ack_rx_local;	        // The outgoing ack signals associated with the input channels

    sc_signal <NoximFlit> flit_tx_local;	// The output channels
    sc_signal <bool> req_tx_local;	        // The requests associated with the output channels
    sc_signal <bool> ack_tx_local;	        // The outgoing ack signals associated with the output channels

    sc_signal <int> free_slots_local;
    sc_signal <int> free_slots_neighbor_local;

    // Instances
    NoximHMRouter *r;		                // Router instance
    NoximProcessingElement *pe;	                // Processing Element instance

    NoximHMCoord* coord;

    void setCoord(int x, int y, int z)
    {
        coord->x=x;
		coord->y=y;
		coord->z=z;
    }

    // Constructor

    SC_CTOR(NoximHMTile) {

	coord = new NoximHMCoord;
	coord->x=0;
	coord->y=0;
	coord->z=0;
	// Router pin assignments
	r = new NoximHMRouter("Router");
	r->clock(clock);
	r->reset(reset);
	for (int i = 0; i < DIRECTIONS_HM; i++) {
	    r->flit_rx[i] (flit_rx[i]);
	    r->req_rx[i] (req_rx[i]);
	    r->ack_rx[i] (ack_rx[i]);

	    r->flit_tx[i] (flit_tx[i]);
	    r->req_tx[i] (req_tx[i]);
	    r->ack_tx[i] (ack_tx[i]);

	    r->free_slots[i] (free_slots[i]);
	    r->free_slots_neighbor[i] (free_slots_neighbor[i]);

	    // NoP
	    r->NoP_data_out[i] (NoP_data_out[i]);
	    r->NoP_data_in[i] (NoP_data_in[i]);
	}

	r->flit_rx[DIRECTION_HM_LOCAL] (flit_tx_local);
	r->req_rx[DIRECTION_HM_LOCAL] (req_tx_local);
	r->ack_rx[DIRECTION_HM_LOCAL] (ack_tx_local);

	r->flit_tx[DIRECTION_HM_LOCAL] (flit_rx_local);
	r->req_tx[DIRECTION_HM_LOCAL] (req_rx_local);
	r->ack_tx[DIRECTION_HM_LOCAL] (ack_rx_local);

	r->free_slots[DIRECTION_HM_LOCAL] (free_slots_local);
	r->free_slots_neighbor[DIRECTION_HM_LOCAL]
	    (free_slots_neighbor_local);

	// Processing Element pin assignments
	pe = new NoximProcessingElement("ProcessingElement");
	pe->clock(clock);
	pe->reset(reset);

	pe->flit_rx(flit_rx_local);
	pe->req_rx(req_rx_local);
	pe->ack_rx(ack_rx_local);

	pe->flit_tx(flit_tx_local);
	pe->req_tx(req_tx_local);
	pe->ack_tx(ack_tx_local);

	pe->free_slots_neighbor(free_slots_neighbor_local);

    }


};

#endif
