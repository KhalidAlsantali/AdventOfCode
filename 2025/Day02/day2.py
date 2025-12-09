filename = "input.txt"
id_list = []
answer = 0

try:
    with open(filename, 'r') as input_file:
        for line in input_file:
            line = line.strip()
            if line:  # Skip empty lines
                id_list = line.split(",")
except FileNotFoundError:
    print(f"Error: Couldn't open file {filename}")


def is_valid_part1(id):
    str_id = str(id)
    if len(str_id) % 2 != 0:
        return True
    
    mid = len(str_id) // 2
    first_half = str_id[:mid]
    second_half = str_id[mid:]
    if first_half == second_half:
        return False

    return True

#2121212121
valid = False
def is_valid_part2(id):
    str_id = str(id)
    for i in range(1, (len(str_id) // 2) + 1):
        if len(str_id) % i == 0:
            sequence = str_id[:i]
            if sequence * (len(str_id) // i) == str_id:
                return False
    return True

for id_range in id_list:
    range_parts = id_range.split("-")
    start = int(range_parts[0])
    end = int(range_parts[-1])
    for i in range(start, end + 1):
        if is_valid_part2(i) == False:
            answer = answer + i

print(answer)