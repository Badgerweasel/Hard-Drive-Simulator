CFLAGS = -ggdb -std=c++11

OBJECTS = FCFSQueueNode.o FCFSQueue.o FCFSDisk.o SameTrackQueueNode.o SameTrackQueue.o SameTrackDisk.o PickUpQueueNode.o PickUpQueue.o PickUpDisk.o LookQueueNode.o LookQueue.o LookDisk.o CLookQueueNode.o CLookQueue.o CLookDisk.o EventQueueNode.o EventQueue.o Event.o Simulation.o main.o

simulation.x: $(OBJECTS)
	g++ $(CFLAGS) $(OBJECTS) -o simulation.x

main.o: main.cpp Simulation.hpp
	g++ -c $(CFLAGS) -o main.o main.cpp

Simulation.o: FCFSDisk.hpp SameTrackDisk.hpp PickUpDisk.hpp LookDisk.hpp CLookDisk.hpp Event.hpp Simulation.hpp Simulation.cpp
	g++ -c $(CFLAGS) -o Simulation.o  Simulation.cpp

Event.o: Event.cpp Event.hpp EventQueue.hpp
	g++ -c $(CFLAGS) -o Event.o Event.cpp

EventQueue.o: EventQueue.hpp EventQueue.cpp EventQueueNode.hpp
	g++ -c $(CFLAGS) -o EventQueue.o EventQueue.cpp

EventQueueNode.o: EventQueueNode.hpp EventQueueNode.cpp Timer.hpp DiskDone.hpp Request.hpp
	g++ -c $(CFLAGS) -o EventQueueNode.o EventQueueNode.cpp

CLookDisk.o: CLookDisk.cpp CLookDisk.hpp CLookQueue.hpp
	g++ -c $(CFLAGS) -o CLookDisk.o CLookDisk.cpp

CLookQueue.o: CLookQueue.cpp CLookQueue.hpp CLookQueueNode.hpp
	g++ -c $(CFLAGS) -o CLookQueue.o CLookQueue.cpp

CLookQueueNode.o: CLookQueueNode.cpp CLookQueueNode.hpp FCFSQueue.hpp
	g++ -c $(CFLAGS) -o CLookQueueNode.o CLookQueueNode.cpp

LookDisk.o: LookDisk.cpp LookDisk.hpp LookQueue.hpp
	g++ -c $(CFLAGS) -o LookDisk.o LookDisk.cpp

LookQueue.o: LookQueue.cpp LookQueue.hpp LookQueueNode.hpp
	g++ -c $(CFLAGS) -o LookQueue.o LookQueue.cpp

LookQueueNode.o: LookQueueNode.cpp LookQueueNode.hpp FCFSQueue.hpp
	g++ -c $(CFLAGS) -o LookQueueNode.o LookQueueNode.cpp

PickUpDisk.o: PickUpDisk.cpp PickUpDisk.hpp PickUpQueue.hpp
	g++ -c $(CFLAGS) -o PickUpDisk.o PickUpDisk.cpp

PickUpQueue.o: PickUpQueue.cpp PickUpQueue.hpp PickUpQueueNode.hpp
	g++ -c $(CFLAGS) -o PickUpQueue.o PickUpQueue.cpp

PickUpQueueNode.o: PickUpQueueNode.cpp PickUpQueueNode.hpp FCFSQueue.hpp
	g++ -c $(CFLAGS) -o PickUpQueueNode.o PickUpQueueNode.cpp

SameTrackDisk.o: SameTrackDisk.cpp SameTrackDisk.hpp SameTrackQueue.hpp
	g++ -c $(CFLAGS) -o SameTrackDisk.o SameTrackDisk.cpp

SameTrackQueue.o: SameTrackQueue.cpp SameTrackQueue.hpp SameTrackQueueNode.hpp
	g++ -c $(CFLAGS) -o SameTrackQueue.o SameTrackQueue.cpp

SameTrackQueueNode.o: SameTrackQueueNode.cpp SameTrackQueueNode.hpp FCFSQueue.hpp
	g++ -c $(CFLAGS) -o SameTrackQueueNode.o SameTrackQueueNode.cpp

FCFSDisk.o: FCFSQueue.hpp FCFSDisk.cpp FCFSDisk.hpp
	g++ -c $(CFLAGS) -o FCFSDisk.o FCFSDisk.cpp

FCFSQueue.o: FCFSQueueNode.hpp FCFSQueue.cpp FCFSQueue.hpp
	g++ -c $(CFLAGS) -o FCFSQueue.o FCFSQueue.cpp

FCFSQueueNode.o: FCFSQueueNode.cpp FCFSQueueNode.hpp
	g++ -c $(CFLAGS) -o FCFSQueueNode.o FCFSQueueNode.cpp

clean:
	rm -fr *~ $(OBJECTS) simulation.x
