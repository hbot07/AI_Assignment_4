import numpy as np

def read_records():
    # read records from file
    with open("records.dat", 'r') as f:
        records = f.readlines()

    # convert records to numpy array of columns
    records = np.array([record.split() for record in records]).T

    return records

def read_bif():
    # read alarm.bif
    with open("alarm.bif", 'r') as f:
        bif = f.readlines()
    list_of_list_of_vars = []
    for line in bif:
        if "probability" in line:
            list_of_vars = [i for i in line.replace(" ", '')
                  .split('(')[1].split(')')[0].split('"') if len(i)!=0]

            list_of_list_of_vars.append(list_of_vars)

    return list_of_list_of_vars

variable_mapping = {'A':0,
                    'B': 1,
                    'C': 2}

list_of_list_of_vars = read_bif()

list_of_list_of_vars = [[variable_mapping[var] for var in list_of_vars] for list_of_vars in list_of_list_of_vars]

print(list_of_list_of_vars)

records = read_records()

records = records == '"True"'
print(records)

for list_of_vars in list_of_list_of_vars:
    from itertools import product

    # Define the length of the permutation
    length = len(list_of_vars)  # Change this to the desired length

    # Create a list of possible values
    values = [True, False]

    # Generate all possible permutations
    permutations = list(product(values, repeat=length))


    for perm in permutations:
        count = np.array([True]*len(records[0]))

        for i in range(len(perm)):
            value_to_search = perm[i]
            column_to_search_in = records[list_of_vars[i]]
            count = count.flatten() & (column_to_search_in.flatten() == value_to_search)
            print(value_to_search, column_to_search_in)

        print(sum(count)/len(count))
