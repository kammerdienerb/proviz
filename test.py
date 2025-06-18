class Interval:
    start_time = 0
    end_time = 0
    events_by_type = {}

    def __init__(self, start_time, end_time):
        self.events_by_type = {}
        self.start_time = start_time
        self.end_time = end_time

    def push_event(self, type, stall):
        if not type in self.events_by_type:
            self.events_by_type[type] = []

        self.events_by_type[type].append(stall)

class Profile:
    intervals = []

    def __init__(self):
        self.intervals = []

    def push_interval(self, start_time, end_time):
        self.intervals.append(Interval(start_time, end_time))

    def push_event(self, type, stall):
        self.intervals[-1].push_event(type, stall)


with open("profile.txt") as f:
    profile = Profile()
    interval_time = 0.02
    cur_time = 0

    stalls = []
    strings = {}

    lines = f.readlines()
    for line in lines:
        split = line.split("\t")
        if split[0] == "e":
            profile.push_event("EU Stall", { "count": int(split[4]), "stack": split[1] })

        elif split[0] == "string":
            strings[split[1]] = split[2]

        elif split[0] == "interval_start":
            time = float(split[2])
            if cur_time == 0:
                cur_time = time
                profile.push_interval(cur_time, cur_time + interval_time)
            elif time >= cur_time + interval_time:
                num_elapsed = int((time - cur_time) / interval_time)
                for i in range(0, num_elapsed):
                    profile.push_interval(cur_time + (interval_time * i), cur_time + (interval_time * (i + 1)))
                cur_time += interval_time * num_elapsed
