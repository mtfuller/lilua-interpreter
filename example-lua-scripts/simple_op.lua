a = 15
b = 5
c = 3

-- w should be 20
-- RPN: w = + a b
--          20
w = a + b
print(w)

-- x should be 25
-- RPN: x = * / a c b
--          * 5 b
--          25
x = a / c * b
print(x)

-- y should be 11
-- RPN: y = + - b / * a c b a
--          + - b / 45 b a
--          + - b 9 a
--          + -4 a
--          11
y = b - a * c / b + a
print(y)

-- z should be 8
-- RPN: z = - + - * 2 a / 30 c b 17
--          - + - 30 / 30 c b 17
--          - + - 30 10 b 17
--          - + 20 b 17
--          - 25 17
--          8
z = 2 * a - 30 / c + b - 17
print(z)
