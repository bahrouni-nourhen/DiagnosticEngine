#ifndef FORMULA_EVALUATOR_H
#define FORMULA_EVALUATOR_H

#include <string>


// FormulaEvaluator = une mini calculatrice.
// Elle sait lire une formule ecrite en texte (ex: "(256*A+B)/4")
// et la calculer en remplacant A et B par de vraies valeurs.
//
// Operations supportees : + - * / et parentheses
// Variables supportees  : A et B (les octets de donnees OBD-II)
class FormulaEvaluator
{

public:

    // Calcule le resultat d'une formule textuelle.
    // A et B sont les octets de donnees (B vaut 0 si non utilise).
    static double evaluate(
        const std::string& formula,
        double A,
        double B = 0.0
    );

};


#endif