#pkg load "control"
pkg load "linear-algebra"

#
# ----------------------
# Budowanie macierzy B
# ----------------------
#
function retval = build_B( r, b, w )
	retval = w * b * transpose( r )
endfunction


#
# ----------------------
# Budowanie maciuerzy S
# ----------------------
#
function retval = build_S( B )
	retval = B + transpose( B )
endfunction

#
# ----------------------
# Budowanie maciuerzy Z
# ----------------------+
#
function retval = build_Z( w, b, r )
	retval = w * cross( b, r )
endfunction

#
# ----------------------
# Oblicza wartosc sigma
# ----------------------
#
function retval = build_Sigma( B )
	retval = trace( B )
endfunction

#
# ----------------------
# Budowanie maciuerzy K
# ----------------------
#
function retval = build_K( S, sigma, z, w )
	K = eye(4)

	q1 = S - sigma * eye( 3 )

	#
	# Cwiartka 1: S - I * sigma
	#
	K( 1, 1 ) = q1( 1, 1 )
	K( 2, 1 ) = q1( 2, 1 )
	K( 3, 1 ) = q1( 3, 1 )

	K( 1, 2 ) = q1( 1, 2 )
	K( 2, 2 ) = q1( 2, 2 )
	K( 3, 2 ) = q1( 3, 2 )

	K( 1, 3 ) = q1( 1, 3 )
	K( 2, 3 ) = q1( 2, 3 )
	K( 3, 3 ) = q1( 3, 3 )

	#
	# Cwiartka 2
	#
	K( 4, 1 ) = z( 1 )
	K( 4, 2 ) = z( 2 )
	K( 4, 3 ) = z( 3 )

	#
	# Cwiartka 4
	#
	K( 4, 4 )  = sigma

	#
	# Cwiartka 1
	#
	K( 1, 4 ) = z( 1 )
	K( 2, 4 ) = z( 2 )
	K( 3, 4 ) = z( 3 )

	retval = ( 1.0 / w ) * K
endfunction

#
# ----------------------
# Budowanie macierzy cros
# ----------------------
#
function retval = build_cros( o )
	res = eye(3)

	res( 1, 1 ) = 0.0
	res( 2, 1 ) = o( 3 )
	res( 3, 1 ) = o( 2 ) * -1.0

	res( 1, 2 ) = o( 3 ) * -1.0
	res( 2, 2 ) = 0.0
	res( 3, 2 ) = o( 1 )

	res( 1, 3 ) = o( 2 )
	res( 2, 3 ) = o( 1 ) * -1.0
	res( 3, 3 ) = 0.0

	retval = res
endfunction

#
# Budowanie macierzy cros
#
function retval = build_omega_cros( omega )
	retval = build_cros( omega )
endfunction

#
# Budowanie macierzy OMEGA, cross omega
#
function retval = build_omega_( om_c, om )
	res         = zeros(4, 4)

	res( 1, 1 ) = om_c( 1, 1 ) * -1
	res( 2, 1 ) = om_c( 2, 1 ) * -1
	res( 3, 1 ) = om_c( 3, 1 ) * -1

	res( 1, 2 ) = om_c( 1, 2 ) * -1
	res( 2, 2 ) = om_c( 2, 2 ) * -1
	res( 3, 2 ) = om_c( 3, 2 ) * -1

	res( 1, 3 ) = om_c( 1, 3 ) * -1
	res( 2, 3 ) = om_c( 2, 3 ) * -1
	res( 3, 3 ) = om_c( 3, 3 ) * -1

	res( 1, 4 ) = om( 1 )
	res( 2, 4 ) = om( 2 )
	res( 3, 4 ) = om( 3 )

	res( 4, 1 ) = om( 1 ) * -1.0
	res( 4, 2 ) = om( 2 ) * -1.0
	res( 4, 3 ) = om( 3 ) * -1.0

	res( 4, 4 ) = 0.0
	retval      = res
endfunction

function retval = build_omega( om )
	omega_c =       build_omega_cros( om )
	retval  = 0.5 * build_omega_( omega_c, om )
endfunction

#
# Budowanie macierzy FI
#
function retval = build_FI( om, dt )
	omega = build_omega( om )
	retval = expm( omega * dt )
endfunction

#
# ----------------------
# Budowanie macierzy Q
# ----------------------
#

# 1. Q11
function retval = build_Q11( Z, sigma, B, eta )
	p1     = ( transpose( Z ) * Z + ( sigma ^ 2 ) - trace( B * transpose( B ) ) )
	p2     = ( transpose( B ) * B - B * B - transpose( B ) * transpose( B ) )
	retval = eta * ( p1  * eye( 3 ) + 2 * p2 )
endfunction

# 2. Q12
# 2.1 Macierz M
function retval = build_M( B, sigma )
	retval = B * ( B - sigma * eye( 3 ) )
endfunction

# 2.2 Macierz y
function retval = build_y( M, sigma )
	v = transpose( M ) - M
	retval = [v( 3, 2 ); v( 1, 3 ); v( 2, 1 )]
endfunction

# 2.3 eta
function retval = build_eta( sigma, SF )
	retval = SF * ( sigma ^ 2 )
endfunction

# 2.4 Q12
function retval = build_Q12( eta, y, B, Z )
	display( y )
	retval = -1.0 * eta * ( y + transpose( B ) * Z )
endfunction

# 3. Q21
function retval = build_Q21( q12 )
	retval = transpose( q12 )
endfunction

# 3. Q22
function retval = build_Q22( eta, B, Z, sigma )
	retval = eta * ( trace( B * transpose( B ) ) + ( sigma ^ 2 ) + transpose( Z ) * Z )
endfunction

function retval = build_Q( Q11, Q12, Q21, Q22 )
	res = eye(4)

	res( 1, 1 ) = Q11( 1, 1 )
	res( 2, 1 ) = Q11( 2, 1 )
	res( 3, 1 ) = Q11( 3, 1 )

	res( 1, 2 ) = Q11( 1, 2 )
	res( 2, 2 ) = Q11( 2, 2 )
	res( 3, 2 ) = Q11( 3, 2 )

	res( 1, 3 ) = Q11( 1, 3 )
	res( 2, 3 ) = Q11( 2, 3 )
	res( 3, 3 ) = Q11( 3, 3 )

	res( 1, 4 ) = Q12( 1 )
	res( 2, 4 ) = Q12( 2 )
	res( 3, 4 ) = Q12( 3 )

	res( 4, 1 ) = Q21( 1 )
	res( 4, 2 ) = Q21( 2 )
	res( 4, 3 ) = Q21( 3 )

	res( 4, 4 ) = Q22

	retval = res
endfunction

#
# ----------------------
# Budoawanie macierzy R
# ----------------------
#
# 1. R11
function retval = build_R11( mi, n, r, b )
	a1 = ( 3.0 - ( transpose( r ) * b ) ^ 2 ) * eye( 3 )
	a2 = ( transpose( b ) * r ) * ( b * transpose( r ) + r * transpose( b ) )
	a3 = build_cros( r ) * ( b * transpose( b ) ) * transpose( build_cros( r ) )

	retval = mi / n * ( a1 + a2 + a3 )
endfunction

# 2. R12
function retval = build_R12()
	retval = [ 0, 0, 0 ]
endfunction

# 4. R21
function retval = build_R21()
	retval = [ 0; 0; 0 ]
endfunction

# 4. R22
function retval = build_R22( mi, n )
	retval = 2 * mi / n
endfunction

function retval = _build_R( R11, R12, R21, R22 )
	res = eye(4)

	res( 1, 1 ) = R11( 1, 1 )
	res( 2, 1 ) = R11( 2, 1 )
	res( 3, 1 ) = R11( 3, 1 )

	res( 1, 2 ) = R11( 1, 2 )
	res( 2, 2 ) = R11( 2, 2 )
	res( 3, 2 ) = R11( 3, 2 )

	res( 1, 3 ) = R11( 1, 3 )
	res( 2, 3 ) = R11( 2, 3 )
	res( 3, 3 ) = R11( 3, 3 )

	res( 1, 4 ) = R12( 1 )
	res( 2, 4 ) = R12( 2 )
	res( 3, 4 ) = R12( 3 )

	res( 4, 1 ) = R21( 1 )
	res( 4, 2 ) = R21( 2 )
	res( 4, 3 ) = R21( 3 )

	res( 4, 4 ) = R22

	retval = res
endfunction

function retval = build_R( mi, n, r, b )

	R11 = build_R11( mi, n, r, b )
	R12 = build_R12()
	R21 = build_R21()
	R22 = build_R22( mi, n )
	retval = _build_R( R11, R12, R21, R22 )

endfunction

#
# ---
# Aktualizacja czasu
# ---
#
function retval = build_K_k1_k( K_k_k, FI_k )
	retval = FI_k * K_k_k * transpose( FI_k )
endfunction

function retval = build_P_k1_k( P_k_k, FI_k, Q_k )
	retval = FI_k * P_k_k * transpose( FI_k ) + Q_k
endfunction

#
# ---
# Aktualizacja pomiaru
# ---
#
# 1. ro
function retval = build_rho_k1( m_k, P_k1_k, delta_m_k1, R_k1 )
	p_tr = trace( P_k1_k )
	a = ( m_k * m_k ) * p_tr
	b = ( m_k * m_k ) * p_tr + ( delta_m_k1 * delta_m_k1 ) * trace( R_k1 )

	retval = a / b
endfunction

# 2. m_k1
function retval = build_m_k1( ro_k1, m_k, delta_m_k1 )
	retval = ( 1 - ro_k1 ) * m_k  + ro_k1 * delta_m_k1
endfunction

# 3. K_k1_k1
function retval = build_K_k1_k1( ro_k1, m_k, m_k1, K_k1_k, delta_m_k1, delta_K_k1 )
	a = ( 1.0 - ro_k1 ) * m_k / m_k1 * K_k1_k
	b = ( ro_k1 * delta_m_k1 / m_k1 ) * delta_K_k1
	retval =  a + b
endfunction

#
# ----------------------
# Oblicznaie wartosci P_n1_n1
# ----------------------
#
# 4. P_k1_k1
function retval = build_P_k1_k1( ro_k1, m_k, m_k1, P_k1_k, delta_m_k1, R_k1 )
	a = ( ( 1 - ro_k1 ) * m_k / m_k1 ) ^ 2
	b = ( ro_k1 * delta_m_k1 / m_k1 ) ^ 2

	retval = a * P_k1_k + b * R_k1
endfunction

#
# ----------------------------------------------------------------------
# Funkcje pomocnicze
# ----------------------------------------------------------------------
#
function retval = d2r( d, m, s, ss )

	rad = d + m / 60.0 + s / 3600.0

	out = 0.0

	if( ss == 1 )
		out = deg2rad( rad * -1.0  )
	else
		out = deg2rad( rad )
	endif

	retval = out

endfunction

function retval = deg2rad(val)
	retval = val / 360.0 * 2.0 * pi
endfunction

function retval = h2r(h, m, s)
	rad = 360.0 * ( h + m / 60.0 + s / 3600.0 ) / 24.0
	retval = deg2rad( rad )
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

function retval = build_rot2( q )

	a = q(1)
	b = q(2) * -1
	c = q(3) * -1
	d = q(4) * -1

	o_11 = a^2 + b^2 - c^2 - d^2
	o_12 = 2 * a * b * c + 2 * a * d
	o_13 = 2 * b * d + 2 * a * c

	o_21 = 2 * b * c + 2 * a * d
	o_22 = a^2 - b^2 + c^2 - d^2
	o_23 = 2 * c * d - 2 * a * b

	o_31 = 2 * b * d - 2 * a * c
	o_32 = 2 * c * d + 2 * a *b
	o_33 = a^2  - b^2 - c^2 + d^2

	ret = eye(3)

	ret(1, 1) = o_11
	ret(2, 1) = o_21
	ret(3, 1) = o_31

	ret(1, 2) = o_12
	ret(2, 2) = o_22
	ret(3, 2) = o_32

	ret(1, 3) = o_13
	ret(2, 3) = o_23
	ret(3, 3) = o_33

	retval = ret

endfunction

function retval = build_rot( q )

	wq = q(1)
	x  = q(2)
	y  = q(3)
	z  = q(4)

	q_11 = 1 - 2 * ( y ^ 2  + z ^ 2 )
	q_12 = 2 * ( x * y - z * wq )
	q_13 = 2 * ( x * z + y * wq )

	q_21 = 2 * ( x * y + z * wq )
	q_22 = 1 - 2 * ( x ^ 2 + z ^ 2 )
	q_23 = 2 * ( y * z - x * wq )

	q_31 = 2 * ( x * z - y * wq )
	q_32 = 2 * ( y * z + x * wq )
	q_33 = 1 - 2 * ( x^2 + y^2 )

#	retval = [q_11, q_12, q_13;
#             q_21, q_22, q_23;
#	          q_31, q_32, q_33]


	retval = [     q_33,      q_32, -1 * q_31;
              -1 * q_23, -1 * q_22,      q_21;
	               q_13,      q_12, -1 * q_11]

endfunction

function retval = roMatrix( alfa, beta, gamma )

	A1 = [ 1, 0,            0;
	       0, cos( alfa ), -1 * sin( alfa );
		   0, sin( alfa ),  1 * cos( alfa ) ]


	A2 = [  1 * cos( beta ), 0, sin( beta );
	        0,               1, 0;
		   -1 * sin( beta ), 0, cos( alfa ) ]

	A3 = [ 1 * cos( gamma ), -1 * sin( gamma ), 0;
	       1 * sin( gamma ),  1 * cos( gamma ), 0;
		                  0,  0,                1 ]
	retval = A1 * A2 * A3

endfunction

#
# -------------------------------------------------------------------
# Funkcje testowe
# -------------------------------------------------------------------
#
# Funkcja geneuje bazowa macierz transformacji
function retval = buildTestMatrix( alfa, beta, gamma )

	rz = rotv ( [0,0,1], alfa )
	ry = rotv ( [0,1,0], beta )
	rx = rotv ( [1,0,0], gamma )
	retval = transpose( rx * ry * rz )

endfunction

#funkcja generuje macierz obrotu dla zadanego czasu
function retval = buildEartRotationMatrix( time )

	rad = ( time / ( 24 * 3600 ) ) * 2.0 * pi
	retval = rotv ( [0,0,1], rad )

endfunction

# Funkcja generuje dane pomiarowe dla pojedynczego obiektu referencyjnego
function retval = buildMeasurment( mrot, t, dT, n, x, y )

	display(x)
	display(y)
	refX  = h2r( x(1), x(2), x(3) )
	refY = d2r( y(1), y(2), y(3), y(4) )

	outmatrixC = eye( 7, n )
	ref = toCartesian( refX, refY )
	ref2 = toCartesian( refX, refY ) * -1

	display(ref)
	display(ref2)
	display("SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS")
	display(toSpeherical( ref ))
	display(toSpeherical( ref2 ))
	dot(ref, ref2)
	acos(dot(ref, ref2))
	display("SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS:1")

	i = 0
	display(t)
	display(dT)
	while( i < n )

		# Nowy czas
		deltaT = t + dT * i

		# Macierz obrotu czasu
		rotTime = buildEartRotationMatrix( deltaT )

		# Symulacja obrotu ukladu wspolrzednych
		newRef = rotTime * ref
		newRef2 = rotTime * ref2

		display("++++++++++++++++++++++++++++++++++")
		display(newRef)
		display(newRef2)

		# Wspolrzedne w ukladzie urzadzenia
		ob = mrot * newRef
		ob2 = mrot * newRef2

		display(toSpeherical( ob ))
		display("-------------------------------")
		display(toSpeherical( ob2 ))
		dot(ob, ob2)
		acos(dot(ob, ob2))
		display("-------------------------------")


		# Wynikowe dane
		outmatrixC(1, i + 1) = newRef(1)
		outmatrixC(2, i + 1) = newRef(2)
		outmatrixC(3, i + 1) = newRef(3)
		outmatrixC(4, i + 1) = ob(1)
		outmatrixC(5, i + 1) = ob(2)
		outmatrixC(6, i + 1) = ob(3)
		outmatrixC(7, i + 1) = deltaT

		i = i + 1
	endwhile
	retval = outmatrixC

endfunction

#
# -------------------------------------------------------------------
# -------------------------------------------------------------------
#
# +0.97310431757312, +0.230363826247709, -0.000703332818416
# -0.23036379880418, +0.97310457073557,  +0.000120888551078
# +0.00071226472952, +0.00004438524887,  +0.999999745354420

#
# -------------------------------------------------------------------
# -------------------------------------------------------------------
# -------------------------------------------------------------------
#
t     = 0


alfa = 30.0/360. * 2.0 * pi()
beta = 30.0/360. * 2.0 * pi()
gamma = 30.0/360. * 2.0 * pi()
rotM  = transpose(buildTestMatrix( alfa, beta, gamma ))
rotMInv = inv( rotM )

dT = 3000

# Syriusz (1)
size = 2
mes1 = buildMeasurment( rotM,                  0, dT, size, [ 11, 03, 43.41 ], [ 61, 45, 06.400, 0 ] )
# Betelgeza (2)
mes2 = buildMeasurment( rotM, mes1(7, size) + dT, dT, size, [ 11, 01, 50.72 ], [ 56, 22, 56.900, 0 ] )
# Aldebaran (3)
mes3 = buildMeasurment( rotM, mes2(7, size) + dT, dT, size, [ 11, 53, 50.09 ], [ 53, 41, 41.490, 0 ] )

#
# 0. Wartosci globalne
#
w       = 1.0 / 16.0

# Blad pomiaru 1 arc min w radianach
err_    = 0.0 * pi() / ( 360.0)
err     = [err_, err_, err_]
epsylon = err

#
# 1. Itercacja numer 0
#

# B_0, S_0, Z_0, sigma_0, K_0
ref       = mes1(1:3, 1)
obs       = mes1(4:6, 1)

B_0       = build_B( ref, obs, w )

S_0       = build_S( B_0 )
Z_0       = build_Z( w, obs, ref )
Z = [	B_0(2, 3) - B_0(3, 2),
		B_0(3, 1) - B_0(1, 3),
		B_0(1, 2) - B_0(2, 1)]


sigma_0   = build_Sigma( B_0 )
delta_K_0 = build_K( S_0, sigma_0, Z_0, w )

# K(0, 0)
# delata_K(0)
K_0_0     = delta_K_0

# delta_m(0)
# m(0)
delta_m_0 = w
m_0       = delta_m_0

# R_0
mi        = sigma_0 ^ 2	# TODO
n         = 1
R_0_0     = build_R( mi, n, ref, obs )
P_0_0     = R_0_0

#
# Dane posrednie
#

P_k_k = P_0_0
K_k_k = K_0_0
m_k   = m_0

# Predkosc rotacji tylko os Z
omega      = [ 0, 0, 2 * pi * 1.0 / ( 24.0 * 3600 ) ]
deltaT     = mes3(7,2) - mes1(7, 1)

# FI(k)
FI_k       = build_FI( omega, deltaT )

# OMEGA(k)
OMEGA_k    = build_omega( omega )

delta_m_k1 = w;

# ++++++++++++++++++++++++++++++++++++++++++++++++++++

#
# 2. Iteracja numer 1
#
ref_k1     = mes2(1:3, 2)
obs_k1     = mes2(4:6, 2)
B_k1       = build_B( ref_k1, obs_k1, w )

S_k1       = build_S( B_k1 )
Z_k1       = build_Z( w, obs_k1, ref_k1 )
sigma_k1   = build_Sigma( B_k1 )
delta_K_k1 = build_K( S_k1, sigma_k1, Z_k1, w )

# R(k + 1)
# mi(k + 1)
# m
n      = 1
mi_k1  = sigma_k1 * sigma_k1	# TODO
R_k1   = build_R( mi_k1, n, ref_k1, obs_k1 )

# Q(k)
ref_k1_eps   = mes2(1:3,2)
obs_k1_eps   = d2r( 0.0, 1.0, 0.0, 0 )
B_k1_eps     = build_B( ref_k1_eps, obs_k1_eps, 1.0 )
S_k1_eps     = build_S( B_k1_eps )
sigma_k1_eps = build_Sigma( B_k1_eps )

eta_k1 = sigma_k1_eps * sigma_k1_eps						# TODO

M_k1   = build_M( B_k1, sigma_k1 )
y_k1   = build_y( M_k1, sigma_k1 )
Q11_k1 = build_Q11( Z_k1, sigma_k1, B_k1, eta_k1 )
Q12_k1 = build_Q12( eta_k1, y_k1, B_k1, Z_k1 )
Q21_k1 = build_Q21( Q12_k1 )
Q22_k1 = build_Q22( eta_k1, B_k1, Z_k1, sigma_k1 )
Q_k1   = build_Q( Q11_k1, Q12_k1, Q21_k1, Q22_k1 )

# K(k+1,k)
# P(k+1, k)
K_k1_k = build_K_k1_k( K_k_k, FI_k )
P_k1_k = build_P_k1_k( P_k_k, FI_k, Q_k1 )

#
# m(k+1)
# RHO(k+1)
# K(k+1, k+1)
# P(k+1, k+1)
#
rho_k1  = build_rho_k1( m_k, P_k1_k, delta_m_k1, R_k1 )
m_k1    = build_m_k1( rho_k1, m_k, delta_m_k1 )
K_k1_k1 = build_K_k1_k1( rho_k1, m_k, m_k1, K_k1_k, delta_m_k1, delta_K_k1 )
P_k1_k1 = build_P_k1_k1( rho_k1, m_k, m_k1, P_k1_k, delta_m_k1, R_k1 )

# ++++++++++++++++++++++++++++++++++++++++++++++++++++

#
# 2. Iteracja numer 2
#
ref_k1     = mes3(1:3, 2)
obs_k1     = mes3(4:6, 2)
B_k1       = build_B( ref_k1, obs_k1, w )

S_k1       = build_S( B_k1 )
Z_k1       = build_Z( w, obs_k1, ref_k1 )
sigma_k1   = build_Sigma( B_k1 )
delta_K_k1 = build_K( S_k1, sigma_k1, Z_k1, w )

# R(k + 1)
# mi(k + 1)
# m
n      = 1
mi_k1  = sigma_k1 * sigma_k1	# TODO
R_k1   = build_R( mi_k1, n, ref_k1, obs_k1 )

# Q(k)
ref_k1_eps   = mes3(1:3,2)
obs_k1_eps   = d2r( 0.0, 1.0, 0.0, 0 )
B_k1_eps     = build_B( ref_k1_eps, obs_k1_eps, 1.0 )
S_k1_eps     = build_S( B_k1_eps )
sigma_k1_eps = build_Sigma( B_k1_eps )

eta_k1 = sigma_k1_eps * sigma_k1_eps						# TODO

M_k1   = build_M( B_k1, sigma_k1 )
y_k1   = build_y( M_k1, sigma_k1 )
Q11_k1 = build_Q11( Z_k1, sigma_k1, B_k1, eta_k1 )
Q12_k1 = build_Q12( eta_k1, y_k1, B_k1, Z_k1 )
Q21_k1 = build_Q21( Q12_k1 )
Q22_k1 = build_Q22( eta_k1, B_k1, Z_k1, sigma_k1 )
Q_k1   = build_Q( Q11_k1, Q12_k1, Q21_k1, Q22_k1 )

# K(k+1,k)
# P(k+1, k)
K_k1_k = build_K_k1_k( K_k_k, FI_k )
P_k1_k = build_P_k1_k( P_k_k, FI_k, Q_k1 )

#
# m(k+1)
# RHO(k+1)
# K(k+1, k+1)
# P(k+1, k+1)
#
rho_k1  = build_rho_k1( m_k, P_k1_k, delta_m_k1, R_k1 )
m_k1    = build_m_k1( rho_k1, m_k, delta_m_k1 )
K_k1_k1 = build_K_k1_k1( rho_k1, m_k, m_k1, K_k1_k, delta_m_k1, delta_K_k1 )
P_k1_k1 = build_P_k1_k1( rho_k1, m_k, m_k1, P_k1_k, delta_m_k1, R_k1 )

display( Q_k1 )
display( R_k1 )
display( P_k1_k1 )

display("------------------------------------------------------------")
display( sigma_k1 )
display( mi_k1 )
display( m_k )
display( R_0_0 )
display( rho_k1 )
display( FI_k )
display( K_k1_k )
display( K_0_0 )
display( K_k1_k1 )

display("------------------------------------------------------------")

[X, Y, W] = eig( K_k1_k1 )

[tmp, idx] = max([Y(1,1),Y(2,2),Y(3,3),Y(4,4)])
XXX = build_rot( X(1:end,idx) )

display("------------------------------------------------------------")
display( X )
display( Y )
display( W )
display("------------------------------------------------------------")
display( rotM )
display("------------------------------------------------------------")
display( XXX )
transpose(XXX)*rotM
display("------------------------------------------------------------")

display( ref_k1 )
display("------------------------------------------------------------")
display( XXX  * ref_k1)
display("-")
display( rotM * ref_k1 )
display("----------")
display( obs_k1 )
display( XXX  * ref_k1 - rotM * ref_k1 )


display("----------")
display("----------")
display("----------")

display( K_k1_k1 )
display( P_k1_k1 )
display( R_k1 )
display( rho_k1 )
display( m_k1 )
display( m_k )
display( delta_m_k1 )
display( sigma_k1 )
display( sigma_k1_eps )

#display( obs )
#display( obs * XXX )

display(rotM)
display(rotMInv)
display(XXX )
display( transpose(XXX) )
display(1)
display( inverse(XXX) )
display(1)
display(XXX * inverse(XXX))
display(1)
display(XXX * inverse(rotM))
display( sigma_0 )
