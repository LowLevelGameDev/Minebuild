# Safe Server
the normal server holds minimal information on the client and trusts the client completly. <br>
Obiously this is good if you want the server to be fast but when connecting with unknown clients who can't be trusted this creates a problem. <br>
<br>
the other server is still safe for the computer running it but clients could lie about the position and therefore allow teleportation, <br>
clients could also lie about health of entities and cause untold errors when synchronizing clients. <br>
<br>
The other server only really exists because if you and a group of friends want to play a game together on an intensive modpack, <br>
in this case you could experience lag spiks and lower frames espically for the person hosting the other server mitigates this. <br>
<br>
For people trying to make public servers this would be a better choice (of course you could also create your own server built on this), <br>
this server holds copies of information held by clients to ensure integerity, it also handles any syncing issues making use of mutexes. <br>
The safe server (this) should still be really fast thanks to the use of mainly spinlocks and use of the udp protocol. <br>
