## 1.1 Part 1
Implement a distributed system consisting of n nodes, numbered 0 to n n 1, arranged in a certain
topology. The topology and information about other parameters will be provided in a configuration
file. A process can exchange messages only with processes that are its neighbors in the given
topology.
All channels in the system are bidirectional, reliable and satisfy the first-in-first-out (FIFO)
property. You can implement a channel using a reliable socket connection via TCP or SCTP
(preferred). For each channel, the socket connection should be created at the beginning of the
program and should stay intact until the end of the program. All messages between neighboring
nodes are exchanged over these connections.
## 1.2 Part 2
Implement a synchronizer to simulate a synchronous distributed system as follows. All nodes
execute a sequence of rounds. In each round, a node sends one message to each of its neighbors,
then waits to receive one message from each of its neighbors sent in that round and then advances
to the next round. Observe that any message received by a node from a “future” round should be
buffered until the node has moved to that round.
## 1.3 Part 3
Design and implement a distributed algorthm that uses the synchronizer built in Part 2 to allow
each node in the system to compute its eccentricity. The eccentricity of a node is defined as the
maximum distance between a node to all other nodes in the topology. Your algorithm can assume
that, initially, all nodes know n in addition to their 1-hop neighbors.
