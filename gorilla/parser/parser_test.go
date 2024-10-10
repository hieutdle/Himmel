package parser

import (
	"fmt"
	"github.com/hieutdle/Himmel/gorilla/ast"
	"github.com/hieutdle/Himmel/gorilla/lexer"
	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
	"testing"
)

func TestLetStatements(t *testing.T) {
	input := `
let x = 5;
let y = 10;
let foobar = 838383;
`

	l := lexer.New(input)
	p := New(l)

	program := p.ParseProgram()
	checkParserErrors(t, p)

	require.NotNil(t, program, "ParseProgram() returned nil")

	assert.Equal(t, 3, len(program.Statements), "program.Statements does not contain 3 statements")

	tests := []struct {
		expectedIdentifier string
	}{
		{"x"},
		{"y"},
		{"foobar"},
	}

	for i, tt := range tests {
		stmt := program.Statements[i]
		assert.True(t, testLetStatement(t, stmt, tt.expectedIdentifier), "Test failed at index %d for expected identifier: %s", i, tt.expectedIdentifier)
	}

}

func testLetStatement(t *testing.T, s ast.Statement, name string) bool {
	if s.TokenLiteral() != "let" {
		t.Errorf("s.TokenLiteral not 'let'. got=%q", s.TokenLiteral())
		return false
	}

	letStmt, ok := s.(*ast.LetStatement)
	if !ok {
		t.Errorf("s not *ast.LetStatement. got=%T", s)
		return false
	}

	if letStmt.Name.Value != name {
		t.Errorf("letStmt.Name.Value not '%s'. got=%s", name, letStmt.Name.Value)
		return false
	}

	if letStmt.Name.TokenLiteral() != name {
		t.Errorf("s.Name not '%s'. got=%s", name, letStmt.Name)
		return false
	}

	return true
}

func checkParserErrors(t *testing.T, p *Parser) {
	errors := p.Errors()
	if len(errors) == 0 {
		return
	}

	t.Errorf("parser has %d errors", len(errors))
	for _, msg := range errors {
		t.Errorf("parser error: %q", msg)
	}
	t.FailNow()
}

func TestReturnStatements(t *testing.T) {
	input := `
return 5;
return 10;
return 993322;
`
	l := lexer.New(input)
	p := New(l)

	program := p.ParseProgram()
	checkParserErrors(t, p)

	assert.Equal(t, 3, len(program.Statements), "program.Statements does not contain 3 statements")

	for _, stmt := range program.Statements {
		returnStmt, ok := stmt.(*ast.ReturnStatement)
		assert.True(t, ok, "stmt not *ast.ReturnStatement. got=%T", stmt)

		assert.Equal(t, "return", returnStmt.TokenLiteral(),
			"returnStmt.TokenLiteral not 'return', got %q", returnStmt.TokenLiteral())
	}

}

func TestIdentifierExpression(t *testing.T) {
	input := "foobar;"

	l := lexer.New(input)
	p := New(l)
	program := p.ParseProgram()
	checkParserErrors(t, p)

	require.Len(t, program.Statements, 1, "program has not enough statements. got=%d", len(program.Statements))

	stmt, ok := program.Statements[0].(*ast.ExpressionStatement)
	require.True(t, ok, "program.Statements[0] is not ast.ExpressionStatement. got=%T", program.Statements[0])

	ident, ok := stmt.Expression.(*ast.Identifier)
	require.True(t, ok, "exp not *ast.Identifier. got=%T", stmt.Expression)

	assert.Equal(t, "foobar", ident.Value, "ident.Value not %s. got=%s", "foobar", ident.Value)
	assert.Equal(t, "foobar", ident.TokenLiteral(), "ident.TokenLiteral not %s. got=%s", "foobar", ident.TokenLiteral())
}

func TestIntegerLiteralExpression(t *testing.T) {
	input := "5;"
	l := lexer.New(input)
	p := New(l)
	program := p.ParseProgram()
	checkParserErrors(t, p)

	require.Len(t, program.Statements, 1, "program has not enough statements. got=%d", len(program.Statements))

	stmt, ok := program.Statements[0].(*ast.ExpressionStatement)
	require.True(t, ok, "program.Statements[0] is not ast.ExpressionStatement. got=%T", program.Statements[0])

	literal, ok := stmt.Expression.(*ast.IntegerLiteral)
	require.True(t, ok, "exp not *ast.IntegerLiteral. got=%T", stmt.Expression)

	assert.Equal(t, int64(5), literal.Value, "literal.Value not %d. got=%d", 5, literal.Value)
	assert.Equal(t, "5", literal.TokenLiteral(), "literal.TokenLiteral not %s. got=%s", "5", literal.TokenLiteral())
}

func TestParsingPrefixExpressions(t *testing.T) {
	prefixTests := []struct {
		input        string
		operator     string
		integerValue int64
	}{
		{"!5;", "!", 5},
		{"-15;", "-", 15},
	}

	for _, tt := range prefixTests {
		l := lexer.New(tt.input)
		p := New(l)
		program := p.ParseProgram()
		checkParserErrors(t, p)

		require.Len(t, program.Statements, 1, "program.Statements does not contain %d statements. got=%d", 1, len(program.Statements))

		stmt, ok := program.Statements[0].(*ast.ExpressionStatement)
		require.True(t, ok, "program.Statements[0] is not ast.ExpressionStatement. got=%T", program.Statements[0])

		exp, ok := stmt.Expression.(*ast.PrefixExpression)
		require.True(t, ok, "stmt is not ast.PrefixExpression. got=%T", stmt.Expression)

		assert.Equal(t, tt.operator, exp.Operator, "exp.Operator is not '%s'. got=%s", tt.operator, exp.Operator)

		assert.True(t, testIntegerLiteral(t, exp.Right, tt.integerValue))
	}
}

func testIntegerLiteral(t *testing.T, il ast.Expression, value int64) bool {
	integ, ok := il.(*ast.IntegerLiteral)
	if !ok {
		assert.Fail(t, "Expression is not *ast.IntegerLiteral", "got=%T", il)
		return false
	}

	assert.Equal(t, value, integ.Value, "integ.Value not %d. got=%d", value, integ.Value)
	assert.Equal(t, fmt.Sprintf("%d", value), integ.TokenLiteral(), "integ.TokenLiteral not %d. got=%s", value, integ.TokenLiteral())

	return true
}

func TestParsingInfixExpressions(t *testing.T) {
	infixTests := []struct {
		input      string
		leftValue  int64
		operator   string
		rightValue int64
	}{
		{"5 + 5;", 5, "+", 5},
		{"5 - 5;", 5, "-", 5},
		{"5 * 5;", 5, "*", 5},
		{"5 / 5;", 5, "/", 5},
		{"5 > 5;", 5, ">", 5},
		{"5 < 5;", 5, "<", 5},
		{"5 == 5;", 5, "==", 5},
		{"5 != 5;", 5, "!=", 5},
	}

	for _, tt := range infixTests {
		l := lexer.New(tt.input)
		p := New(l)
		program := p.ParseProgram()
		checkParserErrors(t, p)

		require.Len(t, program.Statements, 1, "program.Statements does not contain %d statements. got=%d", 1, len(program.Statements))

		stmt, ok := program.Statements[0].(*ast.ExpressionStatement)
		require.True(t, ok, "program.Statements[0] is not ast.ExpressionStatement. got=%T", program.Statements[0])

		exp, ok := stmt.Expression.(*ast.InfixExpression)
		require.True(t, ok, "exp is not ast.InfixExpression. got=%T", stmt.Expression)

		assert.True(t, testIntegerLiteral(t, exp.Left, tt.leftValue))
		assert.Equal(t, tt.operator, exp.Operator, "exp.Operator is not '%s'. got=%s", tt.operator, exp.Operator)
		assert.True(t, testIntegerLiteral(t, exp.Right, tt.rightValue))
	}
}

func TestOperatorPrecedenceParsing(t *testing.T) {
	tests := []struct {
		input    string
		expected string
	}{
		{"-a * b", "((-a) * b)"},
		{"!-a", "(!(-a))"},
		{"a + b + c", "((a + b) + c)"},
		{"a + b - c", "((a + b) - c)"},
		{"a * b * c", "((a * b) * c)"},
		{"a * b / c", "((a * b) / c)"},
		{"a + b / c", "(a + (b / c))"},
		{"a + b * c + d / e - f", "(((a + (b * c)) + (d / e)) - f)"},
		{"3 + 4; -5 * 5", "(3 + 4)((-5) * 5)"},
		{"5 > 4 == 3 < 4", "((5 > 4) == (3 < 4))"},
		{"5 < 4 != 3 > 4", "((5 < 4) != (3 > 4))"},
		{"3 + 4 * 5 == 3 * 1 + 4 * 5", "((3 + (4 * 5)) == ((3 * 1) + (4 * 5)))"},
		{"3 + 4 * 5 == 3 * 1 + 4 * 5", "((3 + (4 * 5)) == ((3 * 1) + (4 * 5)))"},
	}

	for _, tt := range tests {
		l := lexer.New(tt.input)
		p := New(l)
		program := p.ParseProgram()
		checkParserErrors(t, p)

		actual := program.String()
		assert.Equal(t, tt.expected, actual, "expected=%q, got=%q", tt.expected, actual)
	}
}
