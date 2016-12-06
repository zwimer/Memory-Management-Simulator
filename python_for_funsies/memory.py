from chunk import *
#should this be a class?
#we only inted to use one instance; should it just be a module?

class Memory:
    #frames = []
    procs = {}  # Chunks keyed by their process (id)
    chunks = {} # All chunks keyed by starting location
    unused = 0
    size = 0

    def __init__(self, num_frames=256):
        #self.frames = ['.']*num_frames
        self.unused = num_frames
        self.chunks[0] = Chunk(0, num_frames, None)
        self.size = num_frames

    def __str__(self, frames_per_line=32):
        s = ""
        s += "=" * frames_per_line + " "

        #there's a faster way to print than one char at a time
        # but printing doesn't need to be optimal
        for chunk in sorted(self.chunks.keys()):
            for i in range(len(self.chunks[chunk])):
                if len(s) % (frames_per_line+1) == 0:
                    s += "\n"
                if self.chunks[chunk].val == None:
                    s += '.'
                else:
                    s += self.chunks[chunk].val
        s += "\n" + "=" * frames_per_line
        return s

    def get_next_chunk(self, i):
        # EXclusive
        for j in range(i+1, self.size):
            if j in self.chunks:
                return j
        else:
            return None

    def get_prev_chunk(self, i):
        # EXclusive
        for j in reversed(range(0, i)):
            if j in self.chunks:
                return j
        else:
            return None

    def insert_proc(self, p, loc):
        #not to be called for Free memory
        #assume all memory we are replacing is "Free"
        p.addr = loc
        assert p.end() <= self.size
        (is_last, is_first) = (True, True)
        #unless we are flush with the end, create new Free chunk after us
        if p.end() < self.size:
            self.chunks[p.end()] = Chunk(p.end(), self.size-p.end(), None)
        #modify the previous chunk to account for us
        if loc > 0:
            prev = self.get_prev_chunk(loc)
            if self.chunks[prev].end() > loc:
                assert self.chunks[prev].val is None
                self.chunks[prev].length = loc - self.chunks[prev].addr

        self.chunks[loc] = p
        self.unused -= len(p)
        print("Adding " + p.val)
        self.procs[p.val] = p

    def remove_proc(self, p):
        #removes a process and amends the chunks around it
        #not to be called for Free memory
        next_chunk = self.size      #where the extended previous chunk should reach
        print("Popping " + p.val)
        loc = self.procs[p.val].addr
        after = self.get_next_chunk(loc)
        if self.chunks[after].val is None:
            #followed by another Free chunk
            next_chunk = self.chunks[after].end()
            self.chunks.pop(after)
        before = self.get_prev_chunk(loc) 
        if before is None:
            self.chunks[0] = Chunk(0, next_chunk, None)
        elif self.chunks[before].val is None:
            self.chunks[before].length = next_chunk - self.chunks[before].addr
        # else: we are flush with a non-free chunk before us
        self.unused += len(p)


    #alloc algorithms: requires process and returns index
    # all w/ the signature
    #   `fn algo(self, p: Process) -> usize` 
    def next_fit(self, p):
        for i in sorted(self.chunks):
            if self.chunks[i].val is None and len(self.chunks[i]) >= len(p):
                #self.insert_proc(p, i)
                print("Next fit: inserting at ", i)
                return i
        raise ValueError("Couldn't find a next_fit")

    def place_proc(self, proc, algo):
        loc = algo(proc)
        self.insert_proc(proc, loc)


    def simulate(self, procs, algo):
        t = 0
        schedule = {}       #processes keyed by time integer
        #populate
        for p in procs:
            schedule[p.get_next_event(t)] = p
        t = min(schedule)

        #simulate:
        while len(schedule) > 0:
            p = schedule[t]
            (next_t, next_ev) = p.get_next_event(t)
            if next_t is not None:
                schedule[next_t] = p
            if p == Event.arrive:
                self.place_proc(p, algo)
            elif p == Event.finish:
                self.remove_proc(p)

            schedule.pop(t)
            t_ = min(schedule)
            assert t_ > t
            t = t_
