
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

# interleaves two numbers for z-order curve purposes.
# https://graphics.stanford.edu/~seander/bithacks.html#InterleaveTableObvious
# https://upload.wikimedia.org/wikipedia/commons/3/30/Z-curve.svg
def interleave(x,y):
    interleaved = 0
    # get me x's bit at the ith place, put it at the i *2 bit of interleaved
    # get me y's bit at the ith place, put it at the i * 2 + 1 place of interleaved
    for i in range(len(bin(max(x,y))[2:])):
        interleaved |= (x & 1 << i) << i | (y & 1 << i) << (i + 1);

    return interleaved

print(matching_bits(1,3))
print(matching_bits_no_branch(1,3))
print(matching_bits(1,5))
print(matching_bits(1,6))
print(matching_bits(1,14))

print(interleave(7,7)) # 63
print(interleave(7,2)) # 29
print(interleave(2,7)) # 46
