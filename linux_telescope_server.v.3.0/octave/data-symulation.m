pkg load "linear-algebra"


function retval = buildTestMatrix( alfa, beta, gamma )
	rx = rotv ( [1,0,0], alfa )
	ry = rotv ( [0,1,0], beta )
	rz = rotv ( [0,0,1], gamma )
	
	retval = rx * ry * rz

endfunction

function retval = deg2rad(val)
	retval = val / 360.0 * 2.0 * pi
endfunction

function retval = h2r(h, m, s) 
	rad = 360.0 * ( h + m / 60.0 + s / 3600.0 ) / 24.0
	retval = deg2rad( rad )
endfunction

function retval = d2r(c, d, m, s) 
	rad = d + m / 60.0 + s / 3600.0
	retval = c * deg2rad( rad )
endfunction

function retval = toCartesian( x, y)
	res = [0; 0; 0]

	res(1) = cos(y) * cos(x)
	res(2) = cos(y) * sin(x)
	res(3) = sin(y)

	retval = res
endfunction

function retval = toSpeherical( in )
	r = sqrt( in(1) * in(1) + in(2) * in(2) + in(3) * in(3) )
	retval = [atan2(in(2), in(1)),asin(in(3)/r)];
endfunction

#funkcja generuje macierz obrotu dla zadanego czasu
function retval = buildEartRotationMatrix( time )

	rad = ( time / ( 24 * 3600 ) ) * 2.0 * pi
	retval = rotv ( [0,0,1], rad )
		
endfunction

function retval = norm(v)
	retval = 1 / sqrt(v(1) ^ 2 + v(2) ^ 2 + v(3) ^ 2 )
endfunction

function retval = triad(ref1, ref2, obs1, obs2)
	qRef = ref1
	rRef = norm(cross(ref1, ref2)) * cross(ref1, ref2)
	sRef = cross(qRef, rRef)

	qObs = obs1
	rObs = norm(cross(obs1, obs2)) * cross(obs1, obs2)
	sObs = cross(qObs, rObs)

	MR = transpose([qRef(1), qRef(2), qRef(3); rRef(1), rRef(2), rRef(3); sRef(1), sRef(2), sRef(3) ])
	MB = transpose([qObs(1), qObs(2), qObs(3); rObs(1), rObs(2), rObs(3); sObs(1), sObs(2), sObs(3) ])

	retval = MB * inv(MR)
endfunction

function retval = normVec(m)
    ret = [0; 0; 0]
    mm = sqrt(m(1) * m(1) + m(2) * m(2) + m(3) * m(3))
    ret(1) = m(1) / mm
    ret(2) = m(2) / mm
    ret(3) = m(3) / mm  
    
    retval = ret
endfunction

function retval = buildMeasurment( mrot, t, dT, n, x, y )

	display(x)
	display(y)
	refX = h2r( x(1), x(2), x(3) )
	refY = d2r( y(1), y(2), y(3), y(4) )
	
	outmatrixC = eye( 9, n )
	ref = toCartesian( refX, refY )

	i = 0
	display(t)
	display(dT)
	while( i < n )

		# Nowy czas
		deltaT = t + dT * i

		# Macierz obrotu czasu
		rotTime = buildEartRotationMatrix( deltaT )

		# Symulacja obrotu ukladu wspolrzednych	
		newRef = normVec(rotTime * ref)
		
		# Wspolrzedne w ukladzie urzadzenia
		ob = normVec(mrot * newRef)
		
		# Wynikowe dane
		outmatrixC(1, i + 1) = newRef(1)
		outmatrixC(2, i + 1) = newRef(2)
		outmatrixC(3, i + 1) = newRef(3)
		outmatrixC(4, i + 1) = ob(1) + 0.00
		outmatrixC(5, i + 1) = ob(2) + 0.00
		outmatrixC(6, i + 1) = ob(3) + 0.00
		outmatrixC(7, i + 1) = deltaT
		s = toSpeherical( [ob(1), ob(2), ob(3)] )/(2 * pi()) * 360.0
		outmatrixC(8, i + 1) = s(1)
		outmatrixC(9, i + 1) = s(2)
		
		i = i + 1
	endwhile
	retval = outmatrixC
		
endfunction


function retval = build_B( r, b, w )
	retval = w * b * transpose( r )
endfunction

function retval = build_S( B )
	retval = B + transpose( B )
endfunction

function retval = build_Sigma( B )
	retval = trace( B )
endfunction

function retval = build_Z( B )
    display(B)
    retZ = [0;0;0]
    retZ(1) = B(2, 3) - B(3, 2)
    retZ(2) = B(3, 1) - B(1, 3)
    retZ(3) = B(1, 2) - B(2, 1)
    retval = retZ
endfunction

function retval = build_K( S, sigma, Z, w )
	K = eye(4)

	K(1,1) = sigma
	K(1,2) = Z(1)
	K(1,3) = Z(2)
	K(1,4) = Z(3)  

	K(2,1) = Z(1)
	K(2,2) = S(1,1) - sigma
	K(2,3) = S(1,2) 
	K(2,4) = S(1,3)


	K(3,1) = Z(2)
	K(3,2) = S(2,1)
	K(3,3) = S(2,2) - sigma
	K(3,4) = S(2,3)

	K(4,1) = Z(3)
	K(4,2) = S(3,1)
	K(4,3) = S(3,2)
	K(4,4) = S(3,3) - sigma
	
	retval = ( 1.0 / w ) * K
endfunction

function retval = build_Q( lambda, sigma, S, Z )
	eye(3)
	lambda
	sigma
	Z
	v = (lambda + sigma) * eye (3) - S
	display(v)
	inv(v)
    retval = inv(v) * Z
endfunction

function retval = build_rot( Q )

    m = sqrt(1 + transpose(Q) * Q )

    b0 = 1 / m
    b1 = Q(1) / m
    b2 = Q(2) / m
    b3 = Q(3) / m

	retval = [ b0 ^ 2 + b1 ^ 2  - b2 ^ 2 - b3 ^ 2, 2 * (b1 * b2 + b0 * b3),             2 * (b1 * b3 - b0 * b2);
	           2 * (b1 * b2 - b0 * b3),            b0 ^ 2 - b1 ^ 2  + b2 ^ 2 - b3 * b3, 2 * (b2 * b3 + b0 * b1);
	           2 * (b1 * b3 + b0 * b2),            2 * (b2 * b3 - b0 * b1),             b0 ^ 2 - b1 ^ 2 - b2 ^ 2 + b3 ^ 2 ]
endfunction


function retval = funF(K, s)
    retval = det(K - s * eye(4))
endfunction

function retval = poch(K, s)
    retval = ( funF(K, s) + funF(K, s + 0.001) ) / (0.001)
endfunction
display('++++++++++++++++++++++++++++++++')
display('++++++++++++++++++++++++++++++++')
toCartesian(-1.2187534884031, -1.8489904538439)
display('++++++++++++++++++++++++++++++++')
display('++++++++++++++++++++++++++++++++')
display('++++++++++++++++++++++++++++++++')
toCartesian(5.06443181877649, 4.43419485333568)
display('++++++++++++++++++++++++++++++++')
display('++++++++++++++++++++++++++++++++')


alfa = 35.0/360. * 2.0 * pi() 
beta = 67.0/360. * 2.0 * pi()
gamma = 24.0/360. * 2.0 * pi()
MROT = buildTestMatrix( alfa, beta, gamma )

MROT2 = buildTestMatrix( 0.0, 0.0,  5.2142 )


# Syriusz
display('------ Syriusz ------')
ra = h2r(      06, 45, 08.9170) 
dc = d2r(-1.0, 16, 42, 58.0200)

data_syriusz = buildMeasurment( MROT, 0, 3600, 3, [06, 45, 08.9170], [-1.0, 16, 42, 58.0200] )

# Betelgeza
display('--- Betelgeza ---')
ra = h2r(     05, 55, 10.2000) 
dc = d2r(1.0, 07, 24, 25.4300)
data_betelgeza = buildMeasurment( MROT, 0, 3600, 3, [05, 55, 10.2000], [1.0, 07, 24, 25.4300] )


# Aldebaran
display('--- Aldebaran ---')
ra = h2r(     04, 35, 55.2300) 
dc = d2r(1.0, 16, 30, 33.4900)
data_aldebaran = buildMeasurment( MROT, 0, 3600, 3, [04, 35, 55.2300], [1.0, 16, 30, 33.4900] )


ref1 = [data_syriusz(1, 1); data_syriusz(2, 1); data_syriusz(3, 1)]
obs1 = [data_syriusz(4, 1); data_syriusz(5, 1); data_syriusz(6, 1)]
ref2 = [data_betelgeza(1, 2); data_betelgeza(2, 2); data_betelgeza(3, 2)]
obs2 = [data_betelgeza(4, 2); data_betelgeza(5, 2); data_betelgeza(6, 2)]
ref3 = [data_aldebaran(1, 3); data_aldebaran(2, 3); data_aldebaran(3, 3)]
obs3 = [data_aldebaran(4, 3); data_aldebaran(5, 3); data_aldebaran(6, 3)]

TRIAD_ROT = triad(ref1, ref2, obs1, obs2)


# %%%%%%%%%%%%%%%

w1 = 1
w2 = 1
w3 = 1


display('@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@')
display(ref1)
display(obs1)
display(w1)
B1 = build_B(ref1, obs1, w1)
B2 = build_B(ref2, obs2, w2)
B3 = build_B(ref3, obs3, w3)

display(B1)
display(B2)
display(B3)

B     = B1 + B2 #+ B3
S     = build_S(B)
sigma = build_Sigma(B)
Z     = build_Z(B)
K     = build_K(S, sigma, Z, 1.0 )


lambda = w1 + w2 #+ w3
Q     = build_Q(lambda, sigma, S, Z)

Q_ROT = build_rot( Q )



f = funF(K, lambda)
po = poch(K, lambda)

# %%%%%%%%%%%%%%%


MROT
TRIAD_ROT
Q_ROT
TRIAD_ROT * transpose(MROT)
Q_ROT * transpose(MROT)
f
po
f / po
lambda = lambda - f / po
Q     = build_Q(lambda, sigma, S, Z)

Q_ROT2 = build_rot( Q )
Q_ROT2
Q_ROT
TRIAD_ROT
MROT
#data_betelgeza
#data_aldebaran



data_syriusz
data_betelgeza
data_aldebaran
