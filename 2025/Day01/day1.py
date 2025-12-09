dirs = []
distances = []
filename = "input.txt"

try:
    with open(filename, 'r') as input_file:
        for line in input_file:
            line = line.strip()
            if line:  # Skip empty lines
                dirs.append(line[0])
                distances.append(int(line[1:]))
except FileNotFoundError:
    print(f"Error: Couldn't open file {filename}")
    

pointing = 50
answer = 0

# Part 1
# for i in range(len(dirs)):
#     if dirs[i] == 'R':
#         pointing = (pointing + distances[i]) % 100
#
#     if dirs[i] == 'L':
#         pointing = (pointing - distances[i]) % 100
#
#     if pointing == 0:
#         answer += 1

# Part 2
for i in range(len(dirs)):
    if dirs[i] == 'R':
        original_pointing = pointing
        pointing = pointing + distances[i]
        pointing = ((pointing % 100) + 100) % 100
        rotations = (original_pointing + distances[i]) // 100 - (original_pointing // 100)
        answer = answer + rotations
    
    if dirs[i] == 'L':
        original_pointing = pointing
        pointing = pointing - distances[i]
        pointing = ((pointing % 100) + 100) % 100
        rotations = original_pointing // 100 - (original_pointing - distances[i]) // 100
        answer = answer + rotations

    rotations = 0

print(answer)