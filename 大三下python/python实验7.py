import random

while(1):
    doors = {0 : '0', 1 : '0', 2 : '0'}
    number_of_doors = [0, 1, 2]
    car = random.randint(0, 2)
    print("the car door is:", car)
    number_of_doors.remove(car)
    print("the goat doors are:", number_of_doors[0], number_of_doors[-1])
    doors[car] = 'car'
    for i in doors:
        if doors[i] == 'car':
            continue
        else:
            doors[i] = 'goat'
    print(doors)

    player_choose = input("Choose a door to open:")
    player_choose = int(player_choose)
    if doors[player_choose] == 'car':
        host_choose = random.choice(number_of_doors)
        print("\"goat\" behind the door ", host_choose)
        number_of_doors.remove(host_choose)
        print("switch to %d ?(y/n)" % number_of_doors[0])
        switch_choose = input()
        if switch_choose in ['y', 'Y']:
            print("You lose!")
        elif switch_choose in ['n', 'N']:
            print("You win!")
        else:
            print("error input!")
    elif doors[player_choose] == 'goat':
        number_of_doors.remove(player_choose)
        print("\"goat\" behind the door ", number_of_doors[0])
        print("switch to %d ?(y/n)" % car)
        switch_choose = input()
        if switch_choose in ['y', 'Y']:
            print("You win!")
        elif switch_choose in ['n', 'N']:
            print("You lose!")
        else:
            print("error input!")
    else:
        print("error input!")
    print("Do you want to try once more?(y/n)")
    choose = input()
    if choose in ['y', 'Y']:
        continue
    else:
        break








