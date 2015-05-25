import matplotlib.pyplot as plt

ranking = [('Java', 17.110),
           ('C', 17.087),
           ('C#', 8.244),
           ('C++', 8.047),
           ('Objective-C', 7.737),
           ('PHP', 5.555),
           ('(Visual) Basic', 4.369),
           ('JavaScript', 3.386),
           ('Python', 3.291),
           ('Perl', 2.703),
           ('Delphi/Object Pascal', 1.727),
           ('PL/SQL', 1.418),
           ('Ruby', 1.413),
           ('Transact-SQL', 0.925),
           ('Lisp', 0.922),
           ('Visual Basic .NET', 0.784),
           ('Pascal', 0.771),
           ('Logo', 0.717),
           ('Ada', 0.633),
           ('NXT-G', 0.604),
           ('other', 12.5570)]

rates = [x[1] for x in ranking]
labels = [x[0] for x in ranking]
plt.pie(rates, labels=labels)
plt.show()
