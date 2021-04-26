
def matching_bits(a,b):
    width = 8
    matches = 0
    while width:
        if ((a >> width) == (b >> width)):
            matches += 1
        width -= 1

    return matches

def matching_bits_no_branch(a,b):
    width = 8
    matches = 0
    while width:
        matches += int(
            (a >> width) == (b >> width)
        )
        width -= 1
    return matches

def bits_no_match(a,b):
    return matching_bits(a,b) == 0

print(matching_bits(1,3))
print(matching_bits_no_branch(1,3))
print(matching_bits(1,5))
print(matching_bits(1,6))
print(matching_bits(1,14))
