#
# ----------------------
# Budowanie macierzy B
# ----------------------
#
function retval=build_B( r, b, w )
  retval = w * b * transpose( r )
endfunction

#
# ----------------------
# Budowanie maciuerzy S
# ----------------------
#
function retval=build_S( B )
  retval = B + transpose( B )
endfunction

#
# ----------------------
# Budowanie maciuerzy Z
# ----------------------
#
function retval = build_Z( w, b, r )
    retval = cross(w * b, r)
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

    q1 = S - sigma * eye(3)
    
    #
    # Cwiartka 1: S - I * sigma
    #
    K(1,1) = q1(1,1)
    K(2,1) = q1(2,1)
    K(3,1) = q1(3,1)

    K(1,2) = q1(1,2)
    K(2,2) = q1(2,2)
    K(3,2) = q1(3,2)

    K(1,3) = q1(1,3)
    K(2,3) = q1(2,3)
    K(3,3) = q1(3,3)

    #
    # Cwiartka 2
    #
    K(4,1) = z(1)
    K(4,2) = z(2)
    K(4,3) = z(3)

    #
    # Cwiartka 4
    #
    K(4,4)  = sigma

    #
    # Cwiartka 1
    #
    K(1,4) = z(1)
    K(2,4) = z(2)
    K(3,4) = z(3)

    retval = 1.0 /w * K
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

function retval = build_cros_4( o )

  res = eye(4)
  
  res( 1, 1 ) = 0.0
  res( 2, 1 ) = o( 3 ) * -1.0
  res( 3, 1 ) = o( 2 )
  res( 4, 1 ) = o( 2 ) * -1.0
  
  res( 1, 2 ) = o( 3 )
  res( 2, 2 ) = 0.0
  res( 3, 2 ) = o( 1 ) * -1.0
  res( 4, 2 ) = o( 2 ) * -1.0
  
  res( 1, 3 ) = o( 2 ) * -1.0
  res( 2, 3 ) = o( 1 )
  res( 3, 3 ) = 0.0
  res( 4, 3 ) = o( 3 ) * -1.0
  
  res( 2, 4 ) = o( 1 )
  res( 2, 4 ) = o( 2 )
  res( 2, 4 ) = o( 3 )
  res( 2, 4 ) = 0.0

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

  res = eye( 4 )

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
  res( 1, 4 ) = om( 2 )
  res( 1, 4 ) = om( 3 )
  
  res( 4, 1 ) = om( 1 ) * -1.0
  res( 4, 2 ) = om( 2 ) * -1.0
  res( 4, 3 ) = om( 3 ) * -1.0
  
  retval = res  

endfunction

function retval = build_OMEGA( om )  
  
  omega_c = build_omega_cros( om )
  retval = build_omega_( omega_c, om )
    
endfunction
  
#
# Budowanie macierzy FI
#
function retval = build_FI( omega, dt )
  
  retval = expm( omega * dt )
  
endfunction

#
# ----------------------
# Budowanie macierzy Q
# ----------------------
#
# 1. Q11
function retval = build_Q11( Z, sigma, B, eta )
  
  p1 = ( transpose( Z ) * Z + sigma ^ 2 - trace( B * transpose( B ) ) )
  p2 = ( transpose( B ) * B - B * B - transpose( B ) * transpose( B ) )
  
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
  
  retval = SF * sigma
  
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
  
   retval = eta * ( trace( B * transpose( B ) ) + sigma ^ 2 + transpose( Z ) * Z )
   
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

function retval = build_R( R11, R12, R21, R22 )

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

function retval = build_W( K, dt )
  retval = K * dt
endfunction

function retval = build_K_n1_n( K, FI, W )
  retval = FI * K * transpose( FI ) + W
endfunction

#
# ----------------------
# Oblicznaie wartosci ro 
# ----------------------
#
function retval = build_ro( m, P, deltaM, R )
 
  retval = m ^ 2 * trace( P ) / ( ( m ^ 2 ) * trace( P ) + ( deltaM ^ 2 ) * trace( R ) )

endfunction

#
# ----------------------
# Oblicznaie wartosci m_n1
# ----------------------
#
function retval = build_m_n1( ro, m_n, delta_m_n1 )
  
  retal = ( 1- ro ) * m_n  + ro * delta_m_n1
endfunction

#
# ----------------------
# Oblicznaie wartosci K_n1_n1
# ----------------------
#
function retval = build_K_n1_n1( ro_n1, m_n, m_n1, K_n1_n, delta_m_n1, delta_K_n1 )
  
  retval = ( 1.0 - ro_n1 ) * m_n / m_n1 * K_n1_n + ( ro_n1 * delta_m_n1 / m_n1 ) * delta_K_n1
  
endfunction

#
# ----------------------
# Oblicznaie wartosci P_n1_n1
# ----------------------
#
function retval = build_P_n1_n1( ro_n1, m_n, m_n1, P_n1_n, delta_m_n1, R_n1 )
    retval = ( ( ( 1.0 - ro_n1 ) * m_n / m_n1 ) ^ 2 ) * P_n1_n + ( ( ro_n1 * delta_m_n1 / m_n1 ) ^ 2 ) * delta_K_n1
  
endfunction



function retval = build_K_n1( K0, V )
  retval = K0 + V
endfunction

function retval = build_P_n1_n( P, FI, Q )
  retval = FI * P * transpose( FI ) + Q
endfunction

#
# ----------------------------------------------------------------------
# Pomocnicze
# ----------------------------------------------------------------------
#


function retval=d2r(d,m,s,sign)
  rad = d + m / 60.0 + s / 3600.0
  if sign = 1
    retval = deg2rad( rad * -1.0  )
  else
    retval = deg2rad( rad )
  endif
endfunction

function retval=deg2rad(val)
  retval = val/360 * 2.0 * pi
endfunction

function retval=h2r(h,m,s)
  rad = 360.0 * ( h + m / 60.0 + s / 3600.0 ) / 24.0
  retval = deg2rad( rad )
endfunction

function retval=toCartesian( x, y)
	res = [0; 0; 0]

	res(1) = cos(y) * cos(x)
	res(2) = cos(y) * sin(x)
	res(3) = sin(y)
  
  retval = res

endfunction

function retval=toSpeherical( in )
	r = sqrt(in(1) * in(1) + in(2) * in(2) + in(3) * in(3))
	retval = [atan2(in(2), in(1)),asin(in(3)/r)];
endfunction


#
# -------------------------------------------------------------------
# -------------------------------------------------------------------
# -------------------------------------------------------------------
#



#
# Pomiary
#

w     = [0.25, 0.25, 0.25, 0.25]

#
# 1. Obiekt referencyjny
#
refRa   = h2r(6, 45, 08.917);
refDc   = d2r(16, 42, 58.02, 1);

dT = 0;
refDX   = d2r( 145, 03, 34.772380, 1);
refDY   = d2r(  18, 24, 48.927632, 0);

dT1 = 30
vDX1     = d2r( 144, 58, 19.011467, 1);
vDY1     = d2r(  18, 29, 58.823078, 0);

dT2 = 60
vDX2     = d2r( 144, 59, 02.728054, 1);
vDY2     = d2r(  18, 35, 08.384772, 0);

dT3 = 90
vDX3     = d2r( 144, 47, 45.920489, 1);
vDY3     = d2r(  18, 40, 17.611433, 0);

ref1    = toCartesian( refRa, refDc)
a1      = [toCartesian( refDX, refDY),     toCartesian( vDX1, vDY1),       toCartesian( vDX2, vDY2),       toCartesian( vDX3, vDY3)]
a1err   = [toCartesian( 0.00001, 0.00001); toCartesian( 0.00001, 0.00001); toCartesian( 0.00001, 0.00001); toCartesian( 0.00001, 0.00001)]
t1      = [dT, dT1, dT2, dT3]


#
# Obliczenia
#
# Obiekt 1
B = build_B( ref1, a1(1:end,1), w(1) )
S = build_S( B )
Z = build_Z( w(1), a1(1:end,1), ref1 )
sigma = build_Sigma( B )

# R
SF = 1
mi = build_eta( sigma, SF )
n = 1
R11 = build_R11( mi, n, ref1, a1(1:end,1) )
R12 = build_R12()
R21 = build_R21()
R22 = build_R22( mi, n )
R0 = build_R( R11, R12, R21, R22 )

# P
#P0 = R0

# K
#deltaK = build_K( S, sigma, Z, w(1) )

# FI

#dt = 30
#om = [0.000136, -0.000088, 0.000136]
#omega = build_OMEGA( om )  
#FI = build_FI( omega, dt )

# Q

#M = build_M( B, sigma )
#y = build_y( M, sigma )
#eta = build_eta( sigma, SF )

#Q11 = build_Q11( Z, sigma, B, eta )
#Q12 = build_Q12( eta, y, B, Z )
#Q21 = build_Q21( Q12 )
#Q22 = build_Q22( eta, B, Z, sigma )
#Q = build_Q( Q11, Q12, Q21, Q22 )

#P0 = R0
#
#K_n1_n = build_K_n1_n( deltaK, FI, eye(4) )
#P_n1_n = build_P_n1_n( P0, FI, Q )

