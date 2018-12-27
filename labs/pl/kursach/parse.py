#!/bin/python3
# usage:: ./par.py /path/to/file.ged /path/to/file.pl
import sys

# parents(потомок, отец, мать) + золовка (сестра мужа)

if len(sys.argv) < 3:
    print('usage:: ./par.py /path/to/file.ged /path/to/output/file.pl')
    sys.exit(1)


Out = open(sys.argv[2], "w")
Inp = open(sys.argv[1], 'r')

def getString(predicate, items): 
    return \
    Out.write(str(predicate) + "(" + ", ".join(items) + ').\n')


def inpReturn(char): return '\\\'' if char == '\'' else char

def mkStr(s): return str(''.join((inpReturn(i) for i in s)))

people = []
connection = []
is_family = False
id = sex=name=''
fam_members_couunt = -1

for line in Inp.readlines():  # Цикл для каждой строки GEDCOM файла
    l_elem = line.split()

    if l_elem[-1] == 'INDI':  # Ввод информации о новом человеке
        if (id and sex and name)!= '' :
            people.append([id, '\'' + mkStr(' '.join(name)) + '\'',sex])
        id = str(int(line.split('@')[1][1:]))
        # print(id)
        continue
    if l_elem[1] == 'SEX':  # Ввод информации о SeXXуальном человеке
        sex = l_elem[2]
        # print(id)
        continue
    elif l_elem[1] == 'NAME':
        name = l_elem[2:]
        continue

    if l_elem[-1] == 'FAM':
        is_family=True
        # Шаблон словаря родственных связей
        connection.append({"HUSB": '', "WIFE": '', "CHIL": []})
        fam_members_couunt += 1  # Новая связь

    if is_family:  # Запись родственных связей в словарь
        if l_elem[1] == 'HUSB':
            connection[fam_members_couunt]['HUSB'] = str(
                int(l_elem[2].split('@')[1][1:]))

        if l_elem[1] == 'WIFE':
            connection[fam_members_couunt]['WIFE'] = str(
                int(l_elem[2].split('@')[1][1:]))

        if l_elem[1] == 'CHIL':
            connection[fam_members_couunt]['CHIL'].append(
                str(int(l_elem[2].split('@')[1][1:])))

# Out.write('pipl(X).')

only_child = [int(i) for i in range(int(people[0][0]),int(people[-1][0]))]



for i in connection:  # Построение связей мать - ребёнок
    if i['HUSB'] in only_child:
        del only_child[only_child.index(i['HUSB'])]
    
    if i['WIFE'] in only_child:
        del only_child[only_child.index(i['WIFE'])]

    for chil in i['CHIL']:
        # if str(i["WIFE"]) != '':
        getString('parent', [chil, str(i["HUSB"]), str(i["WIFE"])])

# print(only_child)
for i in only_child: 
    if people[0][0]
    getString('parent',['_',str(i),'_'])

for i in people:  # построение соответствий уникального id с именем человка
    getString('pipl',  i[:2])



Inp.close()
Out.close()
