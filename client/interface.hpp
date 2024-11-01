#pragma once
#include <shared/defs.h>

/*
* Interface between server and client
*
*
*/
struct Interface {
  uint64_t seedSize;

  typedef /* define this */ uint64_t entity_uid_t;

  Interface(); // set class variables

  char *getSeed(); // get the seed size

  // entity
  // Define Entity First

  // chunk
  void breakBlock(vec3 chunk, vec3 pos); // tell the server a block has been broken
  void placeBlock(vec3 chunk, vec3 pos); // tell the server a block has been placed

  void brokeBlock(vec3 *chunk, vec3 *pos);  // callback (client should render block broken)
  void placedBlock(vec3 *chunk, vec3 *pos); // callback (client should render block placed)
};