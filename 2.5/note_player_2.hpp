#ifndef _NOTE_PLAYER_2_HPP
#define _NOTE_PLAYER_2_HPP

#include "note_player.hpp"

// ===========================================================================
//
// Prints notes of note_player
//
// ===========================================================================

class note_player_2 : public note_player {
public:
   void play( const note & n ) override;
};
#endif
