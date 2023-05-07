#
# Budowanie macierzy B
#
function retval=build_B_base( r, b, w )
  retval = w * b * transpose( r )
endfunction

#
# Budowanie maciuerzy S
#
function retval=build_S( B )
  retval = B + transpose( B )
endfunction

#
# Budowanie maciuerzy Z
#
function retval = build_z( w, b, r )
    retval = cross(w * b, r)
endfunction

#
# Oblicza wartosc sigma
#
function retval = build_Sigma( B )
    retval = trace( B )
endfunction

#
# Budowanie maciuerzy K
#
function retval = build_K( S, sigma, z )
    K = [0,0,0,0;0,0,0,0;0,0,0,0;0,0,0,0;]

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

    retval = K
endfunction

function retval=build_Omega( ex, v )

  res = [0,0,0,0;0,0,0,0;0,0,0,0;0,0,0,0]

  res(1,1) = -1.0 * ex(1,1)
  res(2,1) = -1.0 * ex(2,1)
  res(3,1) = -1.0 * ex(3,1)

  res(1,2) = -1.0 * ex(1,2)
  res(2,2) = -1.0 * ex(2,2)
  res(3,2) = -1.0 * ex(3,2)

  res(1,3) = -1.0 * ex(1,3)
  res(2,3) = -1.0 * ex(2,3)
  res(3,3) = -1.0 * ex(3,3)

  res(1,4) = v(1)
  res(2,4) = v(2)
  res(3,4) = v(3)

  res(4,1) = -1.0 * v(1)
  res(4,2) = -1.0 * v(2)
  res(4,3) = -1.0 * v(3)

  retval = 0.5 * res

endfunction




function retval=d2r(d,m,s,sign)
  rad = d + m / 60.0 + s / 3600.0
  if sign == 1
    retval = deg2rad( rad * -1.0  )
  else
    retval = deg2rad( rad )
  endif
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

  test = cart2sph(transpose(res))
  display(x)
  display(y)
  display(test)

  retval = res

endfunction

function retval=toSpeherical( in )
	r = sqrt(in(1) * in(1) + in(2) * in(2) + in(3) * in(3))
	retval = [atan2(in(2), in(1)),asin(in(3)/r)];
endfunction

function retval=avarageSpeed( a, t )
  dv = [0,0,0]
	idx = 0
	do
		idx ++
		deltaX = a(1, idx + 1) - a(1, idx)
		deltaY = a(2, idx + 1) - a(2, idx)
    deltaZ = a(3, idx + 1) - a(3, idx)
		deltaT = t(idx + 1) - t (idx)

		dv(1) = dv(1) + deltaX / deltaT
		dv(2) = dv(2) + deltaY / deltaT
    dv(3) = dv(3) + deltaZ / deltaT
	until (idx == 3)

	dv(1) = dv(1) / 3.0
	dv(2) = dv(2) / 3.0
  dv(3) = dv(3) / 3.0

	retval = dv
endfunction

function retval=buildEx( v )
  ex = [0,0,0;0,0,0;0,0,0]

  ex(1,1) = 0
  ex(1,2) = -1 * v(3)
  ex(1,3) = v(2)

  ex(2,1) = v(3)
  ex(2,2) = 0
  ex(2,3) = -1 * v(1)

  ex(3,1) = -1 * v(2)
  ex(3,2) = v(1)
  ex(3,3) = 0

  retval = ex
endfunction



function retval=calculate_mk(mk, w)
  retval = mk + w
endfunction

#
# Oblicza macierz K dla k+1/k+1 - wariant nie optym,alny
#
function retval=build_K_k1_k1( teta, mk, mk1, ak1, K_k1k, delta_K_k1 )
  retval = ( teta * mk / mk1 ) * K_k1k + ( ak1 / mk1 ) * delta_K_k1
endfunction


#
# -------------------------------------------------------------------
# -------------------------------------------------------------------
# -------------------------------------------------------------------
#



function retval=buildB( w, ref, ob)
  retval = transpose( w * build_B_base( ref, ob) )
endfunction

function retval=buildS( b)
  retval = build_S( b )
endfunction

function retval = buildZ(w, b, r)
  retval = build_Z(w * b, r)
endfunction


function retval = buildSigma(b)
  retval = build_Sigma(b)
endfunction

function retval = buildK(S, sigma, z )
  retval = build_K(S, sigma, z )
endfunction

function retval=build_mk(mk, w, i)
  retval = calculate_mk(mk, w(i))
endfunction


function retval=build_fi(omega, deltaT)
  retval = exp( omega * deltaT )
endfunction

function retval=build_K_k1k(fi, K_k)
  retval = fi * K_k * transpose(fi)
endfunction

function retval=build_K_k1(K, w)
  retval = w * K
endfunction


#
# Pomiary
#

#w     = [0.25, 0.25, 0.25, 0.25]

#
# 1. Obiekt referencyjny
#
# refRa   = h2r(6, 45, 08.917);
# refDc   = d2r(16, 42, 58.02, 1);

# dT = 0;
# refDX   = d2r( 145, 03, 34.772380, 1);
# refDY   = d2r(  18, 24, 48.927632, 0);

# dT1 = 30
# vDX1     = d2r( 144, 58, 19.011467, 1);
# vDY1     = d2r(  18, 29, 58.823078, 0);

# dT2 = 60
# vDX2     = d2r( 144, 59, 02.728054, 1);
# vDY2     = d2r(  18, 35, 08.384772, 0);

# dT3 = 90
# vDX3     = d2r( 144, 47, 45.920489, 1);
# vDY3     = d2r(  18, 40, 17.611433, 0);

# ref1    = toCartesian( refRa, refDc)
# a1      = [toCartesian( refDX, refDY),     toCartesian( vDX1, vDY1),       toCartesian( vDX2, vDY2),       toCartesian( vDX3, vDY3)]
# a1err   = [toCartesian( 0.00001, 0.00001); toCartesian( 0.00001, 0.00001); toCartesian( 0.00001, 0.00001); toCartesian( 0.00001, 0.00001)]
# t1      = [dT, dT1, dT2, dT3]


# #
# # Obliczenia
# #
# # Obiekt 1
# #dv1        = avarageSpeed( a1, t1 )
# #dv1err     = avarageSpeed( a1err, t1 )
# #ex1        = buildEx( dv1 )
# #ex1err     = buildEx( dv1err )
# B1         = buildB( w(1), ref1, a1(1:end, 1))
# #B1b        = buildB( w(1), ref1, a1err(1:end, 1))
# S1         = buildS(B1)
# % S1b        = buildS(B1b)
# #Z1         = buildZ( w(1), a1(1:end, 1), ref1)
# % Z1b        = buildZ( w(1), a1err(1:end, 1), ref1)
# #sigma1     = buildSigma(B1)
# % sigma1b    = buildSigma(B1b)
# #deltaK1    = buildK(S1, sigma1, Z1 )
# % V1b        = buildK(S1b, sigma1b, Z1b )
# % m1         = build_mk(m0, w, 1)
# % omega1     = buildOmega(ex1, dv1)
# % omega1b    = buildOmega(ex1err, dv1err)
# % fi1        = build_fi(omega1, 0)
# % fi1b       = build_fi(omega1b, 0)

# % K1_k1      = build_K_k1(deltaK1, w(2))
# % K1_K_k1k   = build_K_k1k(fi1, deltaK1)


# #
# # 2. Obiekt referencyjny
# #
# refRa   = h2r( 4, 35, 55.23);
# refDc   = d2r(16, 30, 33.49, 0);

# dT = 120
# refDX   = d2r( 167, 55, 00.306975, 0);
# refDY   = d2r(  12,  5, 43.748647, 0);

# dT1 = 150
# vDX1     = d2r( 168, 13, 50.955694, 0);
# vDY1     = d2r(  12, 36, 36.809095, 0);

# dT2 = 150
# vDX2     = d2r( 168,  17, 36.918520, 0);
# vDY2     = d2r(  12, 42, 47.674972, 0);

# dT3 = 180
# vDX3     = d2r( 168, 21, 22.828934, 0);
# vDY3     = d2r(  12, 48, 58.624359, 0);

# ref2    = toCartesian( refRa, refDc)
# a2      = [toCartesian( refDX, refDY),     toCartesian( vDX1, vDY1),       toCartesian( vDX2, vDY2),       toCartesian( vDX3, vDY3)]
# a2err   = [toCartesian( 0.00001, 0.00001), toCartesian( 0.00001, 0.00001), toCartesian( 0.00001, 0.00001), toCartesian( 0.00001, 0.00001)]
# t2      = [dT,dT1,dT2,dT3]

# B2         = buildB( w(2), ref2, a2(1:end, 1))
# S2         = buildS(B2)

# #
# # 3. Obiekt referencyjny
# #
# refRa   = h2r(11,  3, 43.67);
# refDc   = d2r(61, 45, 03.72, 0);

# dT = 210
# refDX    = d2r( 79,  4, 59.534046, 0);
# refDY    = d2r( 60,  2, 02.206249, 0);

# dT1 = 240
# vDX1     = d2r( 78, 5, 13.404120, 0);
# vDY1     = d2r( 59, 50, 52.975586, 0);

# dT2 = 270
# vDX2     = d2r( 77, 58, 38.908109, 0);
# vDY2     = d2r( 59, 49, 35.045893, 0);

# dT3 = 300
# vDX3     = d2r( 77, 52,  5.225936, 0);
# vDY3     = d2r( 59, 48, 16.408358, 0);

# ref3    = toCartesian( refRa, refDc)
# a3      = [toCartesian( refDX, refDY),     toCartesian( vDX1, vDY1),       toCartesian( vDX2, vDY2),       toCartesian( vDX3, vDY3)]
# a3err   = [toCartesian( 0.00001, 0.00001), toCartesian( 0.00001, 0.00001), toCartesian( 0.00001, 0.00001), toCartesian( 0.00001, 0.00001)]
# t3      = [dT,dT1,dT2,dT3]

# B3         = buildB( w(3), ref3, a3(1:end, 1))
# S3         = buildS(B3)

# #
# # 4. Obiekt referencyjny
# #
# refRa   = h2r(10, 08, 22.31);
# refDc   = d2r(11, 58,  1.95, 0);

# dT = 330
# refDX    = d2r( 95, 20, 52.283799, 1);
# refDY    = d2r( 69, 11, 21.692567, 0);

# dT1 = 360
# vDX1     = d2r( 90, 52, 10.582028, 1);
# vDY1     = d2r( 69, 15, 40.959152, 0);

# dT2 = 390
# vDX2     = d2r( 90, 31, 27.410827, 1);
# vDY2     = d2r( 69, 15, 44.962040, 0);

# dT3 = 420
# vDX3     = d2r( 90, 10, 44.152168, 1);
# vDY3     = d2r( 69, 15, 46.682690, 0);

# ref4    = toCartesian( refRa, refDc)
# a4      = [toCartesian( refDX, refDY),     toCartesian( vDX1, vDY1),       toCartesian( vDX2, vDY2),       toCartesian( vDX3, vDY3)]
# a4err   = [toCartesian( 0.00001, 0.00001), toCartesian( 0.00001, 0.00001), toCartesian( 0.00001, 0.00001), toCartesian( 0.00001, 0.00001)]
# t4      = [dT,dT1,dT2,dT3]

# B4         = buildB( w(4), ref4, a4(1:end, 1))
# S4         = buildS(B4)


# display(B1)
# display(B2)
# display(B3)
# display(B4)

# display(S1)
# display(S2)
# display(S3)
# display(S4)



# m0    = 0;


# % # Obiekt 2
# % dv2        = avarageSpeed( a2, t2 )
# % dv2err     = avarageSpeed( a2err, t2 )
# % ex2        = buildEx( dv2 )
# % ex2err     = buildEx( dv2err )
# % B2         = buildB( w(2), ref2, a2(1:end, 1))
# % B2b        = buildB( w(2), ref2, a2err(1:end, 1))
# % S2         = buildS(B2)
# % S2b        = buildS(B2b)
# % Z2         = buildZ( w(2), a2(1:end, 1), ref2)
# % Z2b        = buildZ( w(2), a2err(1:end, 1), ref2)
# % sigma2     = buildSigma(B2)
# % sigma2b    = buildSigma(B2b)
# % deltaK2    = buildK(S2, sigma2, Z2 )
# % V2b        = buildK(S2b, sigma2b, Z2b )
# % m2         = build_mk(m1, w, 2)
# % omega2     = buildOmega(ex2, dv2)
# % omega2b    = buildOmega(ex2err, dv2err)
# % fi2        = build_fi(omega2, 30)
# % fi2b       = build_fi(omega2b, 30)

# % K2_k1      = build_K_k1(deltaK2, w(2))
# % K2_K_k1k   = build_K_k1k(fi2, deltaK2)

# % # Obiekt 3
# % dv3        = avarageSpeed( a3, t3 )
# % dv3err     = avarageSpeed( a3err, t3 )
# % ex3        = buildEx( dv3 )
# % ex3err     = buildEx( dv3err )
# % B3         = buildB( w(3), ref3, a3(1:end, 1))
# % B3b        = buildB( w(3), ref3, a3err(1:end, 1))
# % S3         = buildS(B3)
# % S3b        = buildS(B3b)
# % Z3         = buildZ( w(3), a3(1:end, 1), ref3)
# % Z3b        = buildZ( w(3), a3err(1:end, 1), ref3)
# % sigma3     = buildSigma(B3)
# % sigma3b    = buildSigma(B3b)
# % deltaK3    = buildK(S3, sigma3, Z3 )
# % V3b        = buildK(S3b, sigma3b, Z3b )
# % m3         = build_mk(m2, w, 3)
# % omega3     = buildOmega(ex3, dv3)
# % omega3b    = buildOmega(ex3err, dv3err)
# % fi3        = build_fi(omega3, 30)
# % fi3b       = build_fi(omega3b, 30)

# % K3_k1      = build_K_k1(deltaK3, w(3))
# % K3_K_k1k   = build_K_k1k(fi3, deltaK3)


# % # Obiekt 3
# % dv4        = avarageSpeed( a4, t4 )
# % dv4err     = avarageSpeed( a4err, t4 )
# % ex4        = buildEx( dv4 )
# % ex4err     = buildEx( dv4err )
# % B4         = buildB( w(4), ref4, a4(1:end, 1))
# % B4b        = buildB( w(4), ref4, a4err(1:end, 1))
# % S4         = buildS(B4)
# % S4b        = buildS(B4b)
# % Z4         = buildZ( w(4), a4(1:end, 1), ref4)
# % Z4b        = buildZ( w(4), a4err(1:end, 1), ref4)
# % sigma4     = buildSigma(B4)
# % sigma4b    = buildSigma(B4b)
# % deltaK4    = buildK(S4, sigma4, Z4 )
# % V4b        = buildK(S4b, sigma4b, Z4b )
# % m4         = build_mk(m3, w, 4)
# % omega4     = buildOmega(ex4, dv4)
# % omega4b    = buildOmega(ex4err, dv4err)
# % fi4        = build_fi(omega4, 30)
# % fi4b       = build_fi(omega4b, 0)

# % K4_k1      = build_K_k1(deltaK4, w(4))
# % K4_K_k1k   = build_K_k1k(fi4, deltaK4)


# ccx = 1/(360 * 60 * 60) * 1 * 2 * pi
# ccy = 1/(360 * 60 * 60) * 1 * 2 * pi

# #                                                                | 0.000005 |
# #tlinBaseIteration::buildBerr::m.getObservationErrorVector() = | 0.000020 |
# #                                                                | 0.000002 |


# cart = toCartesian( ccx, ccy)
# kk = toSpeherical( [0.000005, 0.000020, 0.000002] )
# x = rad2deg(kk(1))
# y = rad2deg(kk(2))





# #kk2 = toSpeherical( cart )
# #x = rad2deg(kk2(1))
# #y = rad2deg(kk2(2))




# rAlfaErr = 0.000015
# rBetaErr = -0.000028


# errAlfa = rad2deg(rAlfaErr)
# errBeta = rad2deg(rBetaErr)

# cart = toCartesian( abs(rAlfaErr), abs(rBetaErr))





piMs = 1.0 / 24.0 / 3600.0 / 1000.0 * pi()

x = 0.0
y = piMs * 100.0

rot1 = [ 0.492403876506, -0.586824088833, 0.642787609687;
        0.870001903752, 0.310468460973, -0.383022221559;
        0.025201386257, 0.747828070819, 0.663413948169]

rot2 = [ 1.0, 0.0, 0.0;
        0.0, 1.0, 0.0;
        0.0, 0.0, 1.0]

display(rot1)
display(rot2)

cart = toCartesian( x, y )
output = toSpeherical( rot1 * cart )

zero = toSpeherical(rot1 * toCartesian( 0, 0 ))
[x, y]
output
zero

zero - output


