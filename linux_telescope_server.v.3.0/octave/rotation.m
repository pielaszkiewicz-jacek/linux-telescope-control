# Macierz obrotu X
x1 = rotx(45)
y1 = roty(0)
z1 = rotz(0)
rotX = x1 * y1 * z1

# Macierz obrotu Z
x2 = rotx(0)
y2 = roty(0)
z2 = rotz(45)
rotZ = x2 * y2 * z2

# Macierz obrotu XYZ
x3 = rotx(45)
y3 = roty(0)
z3 = rotz(0)
rotXYZ = x3 * y3 * z3

# Konce tubusa
r1 = [0; sqrt(2); 0]
r2 = [0; -1 * sqrt(2); 0]

# Obrot wokol osi X
RA = rotX * r1
RB = rotX * r2

# Przesuniecie wzdloz osi X
rm1 = [1; 0; 0]
RA1 = RA + rm1
RB1 = RB + rm1

# Obrot wokol osi Z
RA2 = rotZ * RA1
RB2 = rotZ * RB1

# Przesuniecie wzdloz osi Z
rm2 = [0; 0; 1]
RA3 = RA2 + rm2
RB3 = RB2 + rm2

# Pochylenie calego urzadzenia
RA4 = rotXYZ * RA3
RB4 = rotXYZ * RB3

# Przesunioecie calego ukladu w osi Z
rm3 = [0; 0; 1]
RA5 = RA4 + rm3
RB5 = RB4 + rm3

RA51 = rotXYZ * ( rotZ * ( ( rotX * r1 ) + rm1 ) + rm2 ) + rm3
RB51 = rotXYZ * ( rotZ * ( ( rotX * r2 ) + rm1 ) + rm2 ) + rm3