from cs50 import SQL


def print_cast():
    # Get the cast of any movie that is present in the IMDb database.
    movie_db = SQL("sqlite:///movies.db")

    movie = input("Which movie's cast do you need? ")

    cast = movie_db.execute(
    "select name from people where id in (select person_id from stars where movie_id = (select id from movies where title = ?))", movie)
    # cast is a list of dictionaries.

    print("\nBelow is the cast: ")
    for crew in cast:
        print("\t"+crew['name'])
    print()


def main():
    print_cast()


if __name__ == "__main__":
    main()
