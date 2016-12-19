from enum import Enum

class Event(Enum):
    arrive  = 0
    finish  = 1


class Chunk:
    #a chunk of contiguous memory
    length = 0      #how many frames are required
    addr = 0      #first frame
    val  = None   #a Process handle or "None" for "free"

    def __init__(self, a, l, v):
        self.length = l
        self.addr = a
        self.val = v

    def __len__(self):
        return self.length
    def end(self):
        return self.addr + len(self)
    #def __equals__(self, other):
    #    return self.val == other.val
    #def __hash__(self):
    #    return hash(self.val)


class Proc(Chunk):
    events = [] # (arrive_time, run_time)
    #NOTE: if this process defrags, then all following events must be delayed
    #   we're dealing w/ tuples, so they'll have to be reformed
    def __init__(self, line):
        #non-emptyness must be checked beforehand
        #not throwing/catching malformed input
        parts = line.split()
        assert len(parts[0]) == 1
        assert 'A' <= parts[0] <= 'Z'
        self.val = parts[0]
        self.length = int(parts[1])
        assert len(parts) > 2
        #events should be backwards so we can pop (_back())
        num_events = len(parts)-2
        self.events = [None]*num_events
        for i in range(2, len(parts)):
            [arr_time, run_time] = parts[i].split('/')
            self.events[num_events-2] = (arr_time, run_time)

    def get_next_event(self, t):
        if len(self.events) == 0:
            return None
        (arr_time, run_time) = self.events[-1]
        if t < arr_time:
            return (arr_time, Event.arrive)
        elif t == arr_time:
            return (arr_time+run_time, Event.run)
        else:
            raise ValueError("Time called after event was done")


