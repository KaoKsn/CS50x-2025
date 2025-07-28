import csv
import sys


# Validate the command line input.
def validate_arguments():
    if len(sys.argv) != 3:
        print("Usage: python dna.py <database.csv> <sequence.txt>")
        sys.exit()


# Try to do both in the same function.
# Read Field Names.
def read_fieldnames():
    str_names = []

    with open(sys.argv[1]) as database:
        reader = csv.DictReader(database)
        str_names = reader.fieldnames

    str_names.remove("name")
    return str_names


# Read the .csv database into the memory.
def read_database():
    # Read each row as dictionary into a list.
    rows = []
    with open(sys.argv[1]) as database:
        reader = csv.DictReader(database)
        for row in reader:
            rows.append(row)
    return rows


# Read the DNA sequence and return it as a string.
def read_sequence():
    sequence = []

    with open(sys.argv[2]) as dna:
        reader = dna.read()
        for char in reader:
            sequence.append(char)

    # Convert sequence into a string.
    sequence = ''.join(sequence)
    return sequence


def str_frequency(sequence, str_names):
    str_list = str_names

    # Calculating the longest match for each str in the sequence.
    str_values = []
    for str_ in str_list:
        str_values.append(longest_match(sequence, str_))
    return str_values


# Return length of longest run of subsequence in sequence
def longest_match(sequence, subsequence):

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


def check_database(str_values, rows, str_names):

    for row in rows:
        match = True
        for i, str_ in enumerate(str_names):
            if int(row[str_]) != str_values[i]:
                match = False
                break
        if match:
            print(row["name"])
            return

    # No match found.
    print("No match")


def main():
    # Check for command-line usage
    validate_arguments()

    # Get all the STRs used using field names - {name field}
    str_names = read_fieldnames()

    # Read database file into a variable.
    rows = read_database()

    # Read DNA sequence file into a variable
    sequence = read_sequence()

    # Find longest match of each STR in DNA sequence
    str_values = str_frequency(sequence, str_names)

    # Check database for matching profiles
    check_database(str_values, rows, str_names)


if __name__ == "__main__":
    main()
