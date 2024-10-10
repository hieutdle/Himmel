package ast

import (
	"github.com/hieutdle/Himmel/gorilla/token"
	"github.com/stretchr/testify/assert"
	"testing"
)

func TestString(t *testing.T) {
	program := &Program{
		Statements: []Statement{
			&LetStatement{
				Token: token.Token{Type: token.LET, Literal: "let"},
				Name: &Identifier{
					Token: token.Token{Type: token.IDENT, Literal: "myVar"},
					Value: "myVar",
				},
				Value: &Identifier{
					Token: token.Token{Type: token.IDENT, Literal: "anotherVar"},
					Value: "anotherVar",
				},
			},
		},
	}

	expected := "let myVar = anotherVar;"
	assert.Equal(t, expected, program.String(), "program.String() wrong. got=%q", program.String())
}
