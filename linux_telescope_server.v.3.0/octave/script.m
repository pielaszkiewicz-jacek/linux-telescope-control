#pkg load "control"
pkg load "linear-algebra"

function retval = euler( alfa, beta, gamma)
	rz = rotv ( [0,0,1], alfa)
	ry = rotv ( [0,1,0], beta)
	rx = rotv ( [1,0,0], gamma)
	retval = ( rx * ry * rz)
endfunction

function retval = normVec(m)
    ret = [0; 0; 0]
    mm = sqrt(m(1) * m(1) + m(2) * m(2) + m(3) * m(3))
    ret(1) = m(1) / mm
    ret(2) = m(2) / mm
    ret(3) = m(3) / mm

    retval = ret
endfunction

function retval = build_B( r, b, w)
	retval = w * b * transpose( r)
endfunction

function retval = build_S( B)
	retval = B + transpose( B)
endfunction

function retval = build_Sigma( B)
	retval = trace( B)
endfunction

function retval = build_Z( B)
    display(B)
    retZ = [0;0;0]
    retZ(1) = B(2, 3) - B(3, 2)
    retZ(2) = B(3, 1) - B(1, 3)
    retZ(3) = B(1, 2) - B(2, 1)
    retval = retZ
endfunction

function retval = build_K( S, sigma, Z, w)
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

	retval = ( 1.0 / w) * K
endfunction

function retval = build_Q( lambda, sigma, S, Z)
    retval = (inv((lambda + sigma) * eye (3) - S) * Z)
endfunction

function retval = toCartesian( x, y)
	res = [0; 0; 0]

	res(1) = cos(y) * cos(x)
	res(2) = cos(y) * sin(x)
	res(3) = sin(y)

	retval = res
endfunction

function retval = build_rot( Q)

    m = sqrt(1 + transpose(Q) * Q)

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



function retval = norm(v)
	retval = 1 / sqrt(v(1) ^ 2 + v(2) ^ 2 + v(3) ^ 2)
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

M = euler( 35/360 * 2 * pi(), 67/360 * 2 * pi(), 24 / 360 * 2 * pi() )

v1N = [1; 0; 0]
v2N = [0; 0; 1]

v1N = toCartesian( 23, 45)
v2N = toCartesian( 125, -10)

display('------------------------')

v1B = normVec(M * v1N) + [0.01;0.01;0.01]
v2B = normVec(M * v2N) + [0.01;0.01;0.01]


#v1B = [ 0.8190; -0.5282; 0.2242]
#v2B = [ -0.3138; -0.1584; 0.9362]

#v1B = [ -0.27991; -0.44454; 0.85090]
#v2B = [ -0.66095;  0.51690; 0.54402]


v1B = normVec(v1B)
v2B = normVec(v2B)

w1 = 1
w2 = 1

B     = build_B(v1N, v1B, w1) + build_B(v2N, v2B, w2)
S     = build_S(B)
sigma = build_Sigma(B)
Z     = build_Z(B)
K     = build_K(S, sigma, Z, 1.0)

lambda = w1 + w2
lambda = 1.9893
Q     = build_Q(lambda, sigma, S, Z)

#rot = build_rot2( Q)

ROT = build_rot( Q)
display(M)
ROT * transpose(M)


fval = funF(K, lambda)
newLambda = lambda - fval / -1.95


XX=triad(v1N, v2N, v1B, v2B)
inv(XX)
display(M)

