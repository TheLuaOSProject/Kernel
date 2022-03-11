.text

.global PORT_IN
.type   PORT_IN, @function
PORT_IN:
    IN      X30, X1, X0
    RET

.global PORT_OUT
.type   PORT_OUT, @function
PORT_OUT:
    RET

.global PORT_WORD_IN
.type   PORT_WORD_IN, @function
PORT_WORD_IN:
    RET
    
.global PORT_WORD_OUT
.type   PORT_WORD_IN, @function
PORT_WORD_OUT:
    RET
    