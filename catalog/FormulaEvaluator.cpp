#include "FormulaEvaluator.h"

#include <cctype>
#include <stdexcept>


// ============================================================
// Partie 1 : remplacer les variables A et B par leurs valeurs
// ============================================================
//
// Exemple : "(256*A+B)/4" avec A=26, B=248
//        -> "(256*26+248)/4"

static std::string substituteVariables(
    const std::string& formula,
    double A,
    double B
)
{
    std::string result;

    for (char c : formula)
    {
        if (c == 'A')
        {
            result += std::to_string(A);
        }
        else if (c == 'B')
        {
            result += std::to_string(B);
        }
        else
        {
            result += c;
        }
    }

    return result;
}


// ============================================================
// Partie 2 : petit parseur d'expression mathematique
// ============================================================
//
// Grammaire simple (priorite des operateurs respectee) :
//
//   expression := terme (('+' | '-') terme)*
//   terme      := facteur (('*' | '/') facteur)*
//   facteur    := nombre | '(' expression ')' | '-' facteur

namespace
{
    // Parseur minimal, garde sa position courante dans "pos"
    class ExpressionParser
    {
    public:
        ExpressionParser(const std::string& text)
        : m_text(text), m_pos(0)
        {
        }

        double parseExpression()
        {
            double value = parseTerm();

            while (peek() == '+' || peek() == '-')
            {
                char op = next();
                double rhs = parseTerm();

                if (op == '+') value += rhs;
                else            value -= rhs;
            }

            return value;
        }

    private:

        std::string m_text;
        size_t m_pos;

        char peek()
        {
            skipSpaces();

            if (m_pos >= m_text.size())
            {
                return '\0';
            }

            return m_text[m_pos];
        }

        char next()
        {
            char c = peek();
            m_pos++;
            return c;
        }

        void skipSpaces()
        {
            while (m_pos < m_text.size() && m_text[m_pos] == ' ')
            {
                m_pos++;
            }
        }

        double parseTerm()
        {
            double value = parseFactor();

            while (peek() == '*' || peek() == '/')
            {
                char op = next();
                double rhs = parseFactor();

                if (op == '*') value *= rhs;
                else            value /= rhs;
            }

            return value;
        }

        double parseFactor()
        {
            if (peek() == '-')
            {
                next();
                return -parseFactor();
            }

            if (peek() == '(')
            {
                next(); // consomme '('
                double value = parseExpression();
                next(); // consomme ')'
                return value;
            }

            return parseNumber();
        }

        double parseNumber()
        {
            skipSpaces();

            size_t start = m_pos;

            while (m_pos < m_text.size() &&
                   (std::isdigit(m_text[m_pos]) || m_text[m_pos] == '.'))
            {
                m_pos++;
            }

            if (start == m_pos)
            {
                throw std::runtime_error(
                    "FormulaEvaluator: caractere inattendu dans la formule"
                );
            }

            return std::stod(m_text.substr(start, m_pos - start));
        }
    };
}


// ============================================================
// Point d'entree public
// ============================================================

double FormulaEvaluator::evaluate(
    const std::string& formula,
    double A,
    double B
)
{
    std::string numericExpression = substituteVariables(formula, A, B);

    ExpressionParser parser(numericExpression);

    return parser.parseExpression();
}