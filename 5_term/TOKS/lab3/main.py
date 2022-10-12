import serial


def redundant_bits_count(m):
    for i in range(m):
        if 2 ** i >= m + i + 1:
            return i
    # If len < 4 (first power of 2)
    return 0


def define_bits_position(data, r):
    if r == 0:
        return data
    j, k, m, res = (0, 0, len(data), '')

    for i in range(1, m + r + 1):
        if i == 2 ** j:
            res = res + 'X'
            j += 1
        else:
            res += data[k]
            k += 1

    return res


def encode_hamming(hamming_encoded, r):
    n = len(hamming_encoded)

    for i in range(r):
        count = 0

        for j in range(2 ** i - 1, n, (2 ** i) * 2):
            # Check all bits in
            for k in range(j, j + 2 ** i):
                if len(hamming_encoded) > k and hamming_encoded[k] == '1':
                    count += 1

            hamming_encoded = hamming_encoded[:2 ** i - 1] + str(count % 2) + hamming_encoded[2 ** i:]

    return hamming_encoded


def detect_errors(hamming_encoded):
    # r - redundant bits count
    r = (len(hamming_encoded) - 1).bit_length()
    n = len(hamming_encoded)
    wrong_bits = []

    for i in range(r):
        count = 0

        for j in range(2 ** i - 1, n, (2 ** i) * 2):
            # Check all bits in
            for k in range(j, j + 2 ** i):
                if len(hamming_encoded) > k != 2 ** i - 1 and hamming_encoded[k] == '1':
                    count += 1

        if hamming_encoded[2 ** i - 1] != str(count % 2):
            wrong_bits.append(2 ** i)

    if len(wrong_bits) != 0:
        wrong_bit = sum(wrong_bits)
        print(f"Error in bits {str(wrong_bits)}. Must change {wrong_bit} bit")
        hamming_encoded = hamming_encoded[:wrong_bit - 1] + str(
            int(not int(hamming_encoded[wrong_bit - 1]))) + hamming_encoded[wrong_bit:]

    return hamming_encoded


def main():
    # data1 = "00110101"
    #
    # r = redundant_bits_count(len(data1))
    # arr_x = define_bits_position(data1, r)
    # # print(arr_x)
    # arr1 = encode_hamming(arr_x, r)
    # # print(arr1)
    # arr1 = "110101100101"  # with error
    # # decoded   XX0X011X0101
    # # right     110101100101
    # # error:    110101101101    error in bits: 0, 7
    #
    # print(f"Wrong: {arr1}")
    # print(f"Right: {detect_errors(arr1)}")
    # arr1 = decode_hamming(arr1)

    input_string = "*"
    data = (''.join(format(ord(x), 'b') for x in input_string))

    n = 10
    chunks = [data[i:i + n] for i in range(0, len(data), n)]

    # Sender routine
    encoded_chunks = []
    for chunk in chunks:
        # Count of additional bits
        redundant_bits = redundant_bits_count(len(chunk))
        # Create new array with empty hamming numbers
        arr = define_bits_position(chunk, redundant_bits)
        # Fill numbers in array
        arr = encode_hamming(arr, redundant_bits)
        encoded_chunks.append(arr)
        print(f"Decoded sender data: {chunk}")
        print(f"Encoded sender data: {arr}" + '\n')

    # Receiver routine
    decoded_chunks = []
    for encoded_chunk in encoded_chunks:
        # Delete all hamming numbers in array
        data = detect_errors(encoded_chunk)
        print(f"Decoded receiver data: {data}" + '\n')
        decoded_chunks.append(data)


if __name__ == '__main__':
    main()
