/*
* Allows the user to choose voxel save or if to connect to an external voxel save,
* (or in other words chooses which server to connect the client to based on user desicion)
*
*
*/

#include <client/client.h>

#include <stdio.h>

int main() {
  Client client;


  if (client.open(Interface{}, 800, 600)) {
    printf("FATAL ERROR    ");
    return 1;
  }

  return 0;
}

