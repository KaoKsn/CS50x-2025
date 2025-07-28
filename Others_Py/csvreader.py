import csv
import sys

def input_sanity():
    if len(sys.argv) != 2:
        print("Input format: python csvreader.py filename.csv")
        sys.exit(1)
    else:
        return

def csvreader():
    # input format: python csvreader.py filename.csv
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)

        # Variables to calculate the favorite language.
        scratch , c , python = 0,0,0

        for row in reader:
            name = row["Name"]
            if name=="python":
                python += 1
            elif name == "C":
                c+=1
            elif name == "scratch":
                scratch += 1
            else:
                print("Something wrong...")

        print(f"C: {c}, Python: {python}, Scratch: {scratch}")
        # if reader = csv.reader(file): reads as a _csvreader, you will have to use indexes.

def betterReader():
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)

        counts = {} # An empty dictionary.

        for row in reader:
            fav_lang = row["Language"]

            # If the key already exists in the counts dictionary,
            if fav_lang in counts:
                counts[fav_lang] += 1
            # Else,
            else:
                counts[fav_lang] = 1

        # Print the most loved lanugage by iterating through each key.
        for language in sorted(counts, key = counts.get , reverse = True):
            print(f"{language}: {counts[language]}")


def main():
    input_sanity()
    betterReader()
    #csvreader()

if __name__ == "__main__":
    main()
