def get_bits(s):
    return "|".join(map(
        lambda x: "".join([i if i != ' ' else '0' for i in reversed(x)]),
        map(lambda x:  "%08s" % bin(ord(x))[2:], s)
    ))


print("```", get_bits("```"))
print("0000", get_bits("0000"))
