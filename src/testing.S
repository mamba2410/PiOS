
.global set_q0
set_q0:
	mov		v0.D[0], x0
	ret

.global set_q2
set_q2:
	mov		v2.D[0], x0
	ret

.global set_q31
set_q31:
	mov		v31.D[0], x0
	ret

.global get_q0
get_q0:
	mov		x0, v0.D[0]
	ret

.global get_q2
get_q2:
	mov		x0, v2.D[0]
	ret

.global get_q31
get_q31:
	mov		x0, v31.D[0]
	ret
