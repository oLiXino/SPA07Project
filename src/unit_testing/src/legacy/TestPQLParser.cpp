#include "PQLParser.h"

#include "catch.hpp"

using namespace std;

SCENARIO("parse an empty query token") {
  queue<QueryToken> tokens;
  PQLParser p = PQLParser();
  const Query q = p.buildQuery(tokens);
  const std::vector<QueryEntity> selectors = q.selectors;

  WHEN("Successfully parsed:") {
    SECTION("selectors: none") { REQUIRE(selectors.size() == 0); }
  }
}

SCENARIO("Only declare one variable a") {
  queue<QueryToken> tokens;
  tokens.push(QueryToken(TokenType::Identifier, "variable"));
  tokens.push(QueryToken(TokenType::Identifier, "a"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  PQLParser p = PQLParser();
  const Query q = p.buildQuery(tokens);
  const std::vector<QueryEntity> selectors = q.selectors;

  WHEN("Successfully parsed:") {
    SECTION("selectors: Only one QueryEntity is parsed inside") {
      REQUIRE(selectors.size() == 1);
      const QueryEntity qe = selectors.front();
      REQUIRE(qe.name == "a");
      REQUIRE(qe.type == QueryEntityType::Variable);
    }
  }
}

SCENARIO("Declare 2 variables a and b") {
  queue<QueryToken> tokens;
  tokens.push(QueryToken(TokenType::Identifier, "variable"));
  tokens.push(QueryToken(TokenType::Identifier, "a"));
  tokens.push(QueryToken(TokenType::Identifier, ","));
  tokens.push(QueryToken(TokenType::Identifier, "b"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  PQLParser p = PQLParser();
  const Query q = p.buildQuery(tokens);
  const std::vector<QueryEntity> selectors = q.selectors;

  WHEN("Successfully parsed:") {
    SECTION("selectors: two QueryEntity are parsed inside") {
      REQUIRE(selectors.size() == 2);
      const QueryEntity qe1 = selectors.front();
      const QueryEntity qe2 = selectors[1];
      REQUIRE(qe1.name == "a");
      REQUIRE(qe1.type == QueryEntityType::Variable);
      REQUIRE(qe2.name == "b");
      REQUIRE(qe2.type == QueryEntityType::Variable);
    }
  }
}

SCENARIO("Declare several different type of query entities, one for each") {
  queue<QueryToken> tokens;
  tokens.push(QueryToken(TokenType::Identifier, "variable"));
  tokens.push(QueryToken(TokenType::Identifier, "a"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  tokens.push(QueryToken(TokenType::Identifier, "procedure"));
  tokens.push(QueryToken(TokenType::Identifier, "p"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  tokens.push(QueryToken(TokenType::Identifier, "stmt"));
  tokens.push(QueryToken(TokenType::Identifier, "s"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  PQLParser p = PQLParser();
  const Query q = p.buildQuery(tokens);
  const std::vector<QueryEntity> selectors = q.selectors;

  WHEN("Successfully parsed:") {
    SECTION("selectors: three QueryEntity are parsed inside") {
      REQUIRE(selectors.size() == 3);
      const QueryEntity qe1 = selectors.front();
      const QueryEntity qe2 = selectors[1];
      const QueryEntity qe3 = selectors[2];
      REQUIRE(qe1.name == "a");
      REQUIRE(qe1.type == QueryEntityType::Variable);
      REQUIRE(qe2.name == "p");
      REQUIRE(qe2.type == QueryEntityType::Procedure);
      REQUIRE(qe3.name == "s");
      REQUIRE(qe3.type == QueryEntityType::Stmt);
    }
  }
}

SCENARIO("Declare several different type of query entities, several for each") {
  queue<QueryToken> tokens;
  tokens.push(QueryToken(TokenType::Identifier, "read"));
  tokens.push(QueryToken(TokenType::Identifier, "r1"));
  tokens.push(QueryToken(TokenType::Identifier, ","));
  tokens.push(QueryToken(TokenType::Identifier, "r2"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  tokens.push(QueryToken(TokenType::Identifier, "if"));
  tokens.push(QueryToken(TokenType::Identifier, "ifs1"));
  tokens.push(QueryToken(TokenType::Identifier, ","));
  tokens.push(QueryToken(TokenType::Identifier, "ifs2"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  tokens.push(QueryToken(TokenType::Identifier, "constant"));
  tokens.push(QueryToken(TokenType::Identifier, "c1"));
  tokens.push(QueryToken(TokenType::Identifier, ","));
  tokens.push(QueryToken(TokenType::Identifier, "c2"));
  tokens.push(QueryToken(TokenType::Identifier, ","));
  tokens.push(QueryToken(TokenType::Identifier, "c3"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  PQLParser p = PQLParser();
  const Query q = p.buildQuery(tokens);
  const std::vector<QueryEntity> selectors = q.selectors;

  WHEN("Successfully parsed:") {
    SECTION("selectors: three types of QueryEntity are parsed inside, and two "
            "for each type") {
      REQUIRE(selectors.size() == 7);
      const QueryEntity qe1 = selectors.front();
      const QueryEntity qe2 = selectors[1];
      const QueryEntity qe3 = selectors[2];
      const QueryEntity qe4 = selectors[3];
      const QueryEntity qe5 = selectors[4];
      const QueryEntity qe6 = selectors[5];
      const QueryEntity qe7 = selectors[6];
      REQUIRE(qe1.name == "r1");
      REQUIRE(qe1.type == QueryEntityType::Read);
      REQUIRE(qe2.name == "r2");
      REQUIRE(qe2.type == QueryEntityType::Read);
      REQUIRE(qe3.name == "ifs1");
      REQUIRE(qe3.type == QueryEntityType::If);
      REQUIRE(qe4.name == "ifs2");
      REQUIRE(qe4.type == QueryEntityType::If);
      REQUIRE(qe5.name == "c1");
      REQUIRE(qe5.type == QueryEntityType::Constant);
      REQUIRE(qe6.name == "c2");
      REQUIRE(qe6.type == QueryEntityType::Constant);
      REQUIRE(qe7.name == "c3");
      REQUIRE(qe7.type == QueryEntityType::Constant);
    }
  }
}

SCENARIO("Select all variables") {
  queue<QueryToken> tokens;
  tokens.push(QueryToken(TokenType::Identifier, "variable"));
  tokens.push(QueryToken(TokenType::Identifier, "a"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  tokens.push(QueryToken(TokenType::Identifier, "Select"));
  tokens.push(QueryToken(TokenType::Identifier, "a"));
  PQLParser p = PQLParser();
  const Query q = p.buildQuery(tokens);
  const std::vector<QueryEntity> selectors = q.selectors;
  const std::vector<QueryEntity> tar = q.target;

  WHEN("Successfully parsed:") {
    SECTION("selectors: one QueryEntity is inside") {
      REQUIRE(selectors.size() == 1);
      const QueryEntity qe = selectors.front();
      REQUIRE(qe.name == "a");
      REQUIRE(qe.type == QueryEntityType::Variable);
    }
    SECTION("target") {
      REQUIRE(tar.front().name == "a");
      REQUIRE(tar.front().type == QueryEntityType::Variable);
    }
  }
}

SCENARIO("Including one such that clause") {
  SECTION("One valid Follows clause") {
    queue<QueryToken> tokens;
    tokens.push(QueryToken(TokenType::Identifier, "assign"));
    tokens.push(QueryToken(TokenType::Identifier, "a"));
    tokens.push(QueryToken(TokenType::Identifier, ";"));
    tokens.push(QueryToken(TokenType::Identifier, "Select"));
    tokens.push(QueryToken(TokenType::Identifier, "a"));
    tokens.push(QueryToken(TokenType::Identifier, "such that"));
    tokens.push(QueryToken(TokenType::Identifier, "Follows"));
    tokens.push(QueryToken(TokenType::Identifier, "("));
    tokens.push(QueryToken(TokenType::Identifier, "a"));
    tokens.push(QueryToken(TokenType::Identifier, ","));
    tokens.push(QueryToken(TokenType::Identifier, "5"));
    tokens.push(QueryToken(TokenType::Identifier, ")"));
    PQLParser p = PQLParser();
    Query q = p.buildQuery(tokens);
    std::vector<QueryEntity> selectors = q.selectors;
    std::vector<Clause> clauses = q.clauses;
	std::vector<QueryEntity> tar = q.target;

    WHEN("Successfully parsed:") {
      SECTION("selectors: one QueryEntity is inside") {
        REQUIRE(selectors.size() == 1);
        QueryEntity qe = selectors.front();
        REQUIRE(qe.name == "a");
        REQUIRE(qe.type == QueryEntityType::Assign);
      }
      SECTION("target") {
        REQUIRE(tar.front().name == "a");
        REQUIRE(tar.front().type == QueryEntityType::Assign);
      }
      SECTION("clauses: one Follows clause is inside") {
        REQUIRE(clauses.size() == 1);
        Clause c = clauses.front();
        std::vector<QueryEntity> parameters = c.parameters;
        REQUIRE(c.clauseType == ClauseType::Follows);
        REQUIRE(parameters[0].name == "a");
        REQUIRE(parameters[0].type == QueryEntityType::Assign);
        REQUIRE(parameters[1].name == "5");
        REQUIRE(parameters[1].type == QueryEntityType::Line);
      }
    }
  }
  SECTION("One valid Follows* clause") {
    queue<QueryToken> tokens;
    tokens.push(QueryToken(TokenType::Identifier, "while"));
    tokens.push(QueryToken(TokenType::Identifier, "w"));
    tokens.push(QueryToken(TokenType::Identifier, ";"));
    tokens.push(QueryToken(TokenType::Identifier, "Select"));
    tokens.push(QueryToken(TokenType::Identifier, "w"));
    tokens.push(QueryToken(TokenType::Identifier, "such that"));
    tokens.push(QueryToken(TokenType::Identifier, "Follows*"));
    tokens.push(QueryToken(TokenType::Identifier, "("));
    tokens.push(QueryToken(TokenType::Identifier, "w"));
    tokens.push(QueryToken(TokenType::Identifier, ","));
    tokens.push(QueryToken(TokenType::Identifier, "_"));
    tokens.push(QueryToken(TokenType::Identifier, ")"));
    PQLParser p = PQLParser();
    Query q = p.buildQuery(tokens);
    std::vector<QueryEntity> selectors = q.selectors;
    std::vector<Clause> clauses = q.clauses;
	std::vector<QueryEntity> tar = q.target;
    WHEN("Successfully parsed:") {
      SECTION("selectors: one QueryEntity is inside") {
        REQUIRE(selectors.size() == 1);
        QueryEntity qe = selectors.front();
        REQUIRE(qe.name == "w");
        REQUIRE(qe.type == QueryEntityType::While);
      }
      SECTION("target") {
        REQUIRE(tar.front().name == "w");
        REQUIRE(tar.front().type == QueryEntityType::While);
      }
      SECTION("clauses: one FollowsT clause is inside") {
        REQUIRE(clauses.size() == 1);
        Clause c = clauses.front();
        std::vector<QueryEntity> parameters = c.parameters;
        REQUIRE(c.clauseType == ClauseType::FollowsT);
        REQUIRE(parameters[0].name == "w");
        REQUIRE(parameters[0].type == QueryEntityType::While);
        REQUIRE(parameters[1].name == "_");
        REQUIRE(parameters[1].type == QueryEntityType::Underscore);
      }
    }
  }
  SECTION("One valid Parent clause") {
    queue<QueryToken> tokens;
    tokens.push(QueryToken(TokenType::Identifier, "call"));
    tokens.push(QueryToken(TokenType::Identifier, "c"));
    tokens.push(QueryToken(TokenType::Identifier, ";"));
    tokens.push(QueryToken(TokenType::Identifier, "Select"));
    tokens.push(QueryToken(TokenType::Identifier, "c"));
    tokens.push(QueryToken(TokenType::Identifier, "such that"));
    tokens.push(QueryToken(TokenType::Identifier, "Parent"));
    tokens.push(QueryToken(TokenType::Identifier, "("));
    tokens.push(QueryToken(TokenType::Identifier, "_"));
    tokens.push(QueryToken(TokenType::Identifier, ","));
    tokens.push(QueryToken(TokenType::Identifier, "c"));
    tokens.push(QueryToken(TokenType::Identifier, ")"));
    PQLParser p = PQLParser();
    Query q = p.buildQuery(tokens);
    std::vector<QueryEntity> selectors = q.selectors;
    std::vector<Clause> clauses = q.clauses;
	std::vector<QueryEntity> tar = q.target;
    WHEN("Successfully parsed:") {
      SECTION("selectors: one QueryEntity is inside") {
        REQUIRE(selectors.size() == 1);
        QueryEntity qe = selectors.front();
        REQUIRE(qe.name == "c");
        REQUIRE(qe.type == QueryEntityType::Call);
      }
      SECTION("target") {
        REQUIRE(tar.front().name == "c");
        REQUIRE(tar.front().type == QueryEntityType::Call);
      }
      SECTION("clauses: one Parent clause is inside") {
        REQUIRE(clauses.size() == 1);
        Clause c = clauses.front();
        std::vector<QueryEntity> parameters = c.parameters;
        REQUIRE(c.clauseType == ClauseType::Parent);
        REQUIRE(parameters[0].name == "_");
        REQUIRE(parameters[0].type == QueryEntityType::Underscore);
        REQUIRE(parameters[1].name == "c");
        REQUIRE(parameters[1].type == QueryEntityType::Call);
      }
    }
  }
  SECTION("One valid Parent* clause") {
    queue<QueryToken> tokens;
    tokens.push(QueryToken(TokenType::Identifier, "print"));
    tokens.push(QueryToken(TokenType::Identifier, "pr"));
    tokens.push(QueryToken(TokenType::Identifier, ";"));
    tokens.push(QueryToken(TokenType::Identifier, "Select"));
    tokens.push(QueryToken(TokenType::Identifier, "pr"));
    tokens.push(QueryToken(TokenType::Identifier, "such that"));
    tokens.push(QueryToken(TokenType::Identifier, "Parent*"));
    tokens.push(QueryToken(TokenType::Identifier, "("));
    tokens.push(QueryToken(TokenType::Identifier, "_"));
    tokens.push(QueryToken(TokenType::Identifier, ","));
    tokens.push(QueryToken(TokenType::Identifier, "pr"));
    tokens.push(QueryToken(TokenType::Identifier, ")"));
    PQLParser p = PQLParser();
    Query q = p.buildQuery(tokens);
    std::vector<QueryEntity> selectors = q.selectors;
    std::vector<Clause> clauses = q.clauses;
	std::vector<QueryEntity> tar = q.target;
    WHEN("Successfully parsed:") {
      SECTION("selectors: one QueryEntity is inside") {
        REQUIRE(selectors.size() == 1);
        QueryEntity qe = selectors.front();
        REQUIRE(qe.name == "pr");
        REQUIRE(qe.type == QueryEntityType::Print);
      }
      SECTION("target") {
        REQUIRE(tar.front().name == "pr");
        REQUIRE(tar.front().type == QueryEntityType::Print);
      }
      SECTION("clauses: one ParentT clause is inside") {
        REQUIRE(clauses.size() == 1);
        Clause c = clauses.front();
        std::vector<QueryEntity> parameters = c.parameters;
        REQUIRE(c.clauseType == ClauseType::ParentT);
        REQUIRE(parameters[0].name == "_");
        REQUIRE(parameters[0].type == QueryEntityType::Underscore);
        REQUIRE(parameters[1].name == "pr");
        REQUIRE(parameters[1].type == QueryEntityType::Print);
      }
    }
  }
  SECTION("One valid Modifies clause") {
    queue<QueryToken> tokens;
    tokens.push(QueryToken(TokenType::Identifier, "prog_line"));
    tokens.push(QueryToken(TokenType::Identifier, "pl"));
    tokens.push(QueryToken(TokenType::Identifier, ";"));
    tokens.push(QueryToken(TokenType::Identifier, "variable"));
    tokens.push(QueryToken(TokenType::Identifier, "v"));
    tokens.push(QueryToken(TokenType::Identifier, ";"));
    tokens.push(QueryToken(TokenType::Identifier, "Select"));
    tokens.push(QueryToken(TokenType::Identifier, "pl"));
    tokens.push(QueryToken(TokenType::Identifier, "such that"));
    tokens.push(QueryToken(TokenType::Identifier, "Modifies"));
    tokens.push(QueryToken(TokenType::Identifier, "("));
    tokens.push(QueryToken(TokenType::Identifier, "10"));
    tokens.push(QueryToken(TokenType::Identifier, ","));
    tokens.push(QueryToken(TokenType::Identifier, "v"));
    tokens.push(QueryToken(TokenType::Identifier, ")"));
    PQLParser p = PQLParser();
    Query q = p.buildQuery(tokens);
    std::vector<QueryEntity> selectors = q.selectors;
    std::vector<Clause> clauses = q.clauses;
	std::vector<QueryEntity> tar = q.target;
    WHEN("Successfully parsed:") {
      SECTION("selectors: two QueryEntity is inside") {
        REQUIRE(selectors.size() == 2);
        QueryEntity qe = selectors.front();
        QueryEntity qe2 = selectors[1];
        REQUIRE(qe.name == "pl");
        REQUIRE(qe.type == QueryEntityType::Progline);
        REQUIRE(qe2.name == "v");
        REQUIRE(qe2.type == QueryEntityType::Variable);
      }
      SECTION("target") {
        REQUIRE(tar.front().name == "pl");
        REQUIRE(tar.front().type == QueryEntityType::Progline);
      }
      SECTION("clauses: one ModifiesS clause is inside") {
        REQUIRE(clauses.size() == 1);
        Clause c = clauses.front();
        std::vector<QueryEntity> parameters = c.parameters;
        REQUIRE(c.clauseType == ClauseType::ModifiesS);
        REQUIRE(parameters[0].name == "10");
        REQUIRE(parameters[0].type == QueryEntityType::Line);
        REQUIRE(parameters[1].name == "v");
        REQUIRE(parameters[1].type == QueryEntityType::Variable);
      }
    }
  }
  SECTION("One valid Uses clause") {
    queue<QueryToken> tokens;
    tokens.push(QueryToken(TokenType::Identifier, "variable"));
    tokens.push(QueryToken(TokenType::Identifier, "v"));
    tokens.push(QueryToken(TokenType::Identifier, ";"));
    tokens.push(QueryToken(TokenType::Identifier, "Select"));
    tokens.push(QueryToken(TokenType::Identifier, "v"));
    tokens.push(QueryToken(TokenType::Identifier, "such that"));
    tokens.push(QueryToken(TokenType::Identifier, "Uses"));
    tokens.push(QueryToken(TokenType::Identifier, "("));
    tokens.push(QueryToken(TokenType::Identifier, "\""));
    tokens.push(QueryToken(TokenType::Identifier, "proc1"));
    tokens.push(QueryToken(TokenType::Identifier, "\""));
    tokens.push(QueryToken(TokenType::Identifier, ","));
    tokens.push(QueryToken(TokenType::Identifier, "\""));
    tokens.push(QueryToken(TokenType::Identifier, "var1"));
    tokens.push(QueryToken(TokenType::Identifier, "\""));
    tokens.push(QueryToken(TokenType::Identifier, ")"));
    PQLParser p = PQLParser();
    Query q = p.buildQuery(tokens);
    std::vector<QueryEntity> selectors = q.selectors;
    std::vector<Clause> clauses = q.clauses;
	std::vector<QueryEntity> tar = q.target;
    WHEN("Successfully parsed:") {
      SECTION("selectors: one QueryEntity is inside") {
        REQUIRE(selectors.size() == 1);
        QueryEntity qe = selectors.front();
        REQUIRE(qe.name == "v");
        REQUIRE(qe.type == QueryEntityType::Variable);
      }
      SECTION("target") {
        REQUIRE(tar.front().name == "v");
        REQUIRE(tar.front().type == QueryEntityType::Variable);
      }
      SECTION("clauses: one UsesS clause is inside") {
        REQUIRE(clauses.size() == 1);
        Clause c = clauses.front();
        std::vector<QueryEntity> parameters = c.parameters;
        REQUIRE(c.clauseType == ClauseType::UsesS);
        REQUIRE(parameters[0].name == "proc1");
        REQUIRE(parameters[0].type == QueryEntityType::Name);
        REQUIRE(parameters[1].name == "var1");
        REQUIRE(parameters[1].type == QueryEntityType::Name);
      }
    }
  }
}

SCENARIO("Test pattern clause exact match") {
  queue<QueryToken> tokens;
  tokens.push(QueryToken(TokenType::Identifier, "assign"));
  tokens.push(QueryToken(TokenType::Identifier, "a"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  tokens.push(QueryToken(TokenType::Identifier, "variable"));
  tokens.push(QueryToken(TokenType::Identifier, "v"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  tokens.push(QueryToken(TokenType::Identifier, "Select"));
  tokens.push(QueryToken(TokenType::Identifier, "a"));
  tokens.push(QueryToken(TokenType::Identifier, "pattern"));
  tokens.push(QueryToken(TokenType::Identifier, "a"));
  tokens.push(QueryToken(TokenType::Identifier, "("));
  tokens.push(QueryToken(TokenType::Identifier, "_"));
  tokens.push(QueryToken(TokenType::Identifier, ","));
  tokens.push(QueryToken(TokenType::Identifier, "\""));
  tokens.push(QueryToken(TokenType::Identifier, "v+x * (y8y +z)* t"));
  tokens.push(QueryToken(TokenType::Identifier, "\""));
  tokens.push(QueryToken(TokenType::Identifier, ")"));
  tokens.push(QueryToken(TokenType::Identifier, "such that"));
  tokens.push(QueryToken(TokenType::Identifier, "Modifies"));
  tokens.push(QueryToken(TokenType::Identifier, "("));
  tokens.push(QueryToken(TokenType::Identifier, "a"));
  tokens.push(QueryToken(TokenType::Identifier, ","));
  tokens.push(QueryToken(TokenType::Identifier, "v"));
  tokens.push(QueryToken(TokenType::Identifier, ")"));
  PQLParser p = PQLParser();
  Query q = p.buildQuery(tokens);
  std::vector<Clause> clauses = q.clauses;
  SECTION("clauses: one AssignPatt clause is inside") {
    REQUIRE(clauses.size() == 2);
    Clause c = clauses.front();
    std::vector<QueryEntity> parameters = c.parameters;
    REQUIRE(c.clauseType == ClauseType::AssignPatt);
    REQUIRE(parameters[0].name == "a");
    REQUIRE(parameters[0].type == QueryEntityType::Assign);
    REQUIRE(parameters[1].name == "_");
    REQUIRE(parameters[1].type == QueryEntityType::Underscore);
    REQUIRE(parameters[2].name == " v x y8y z + * t * + ");
    REQUIRE(parameters[2].type == QueryEntityType::Expression);
  }
}

SCENARIO("Test pattern clause partial match") {
  queue<QueryToken> tokens;
  tokens.push(QueryToken(TokenType::Identifier, "assign"));
  tokens.push(QueryToken(TokenType::Identifier, "a"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  tokens.push(QueryToken(TokenType::Identifier, "variable"));
  tokens.push(QueryToken(TokenType::Identifier, "v"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  tokens.push(QueryToken(TokenType::Identifier, "Select"));
  tokens.push(QueryToken(TokenType::Identifier, "a"));
  tokens.push(QueryToken(TokenType::Identifier, "pattern"));
  tokens.push(QueryToken(TokenType::Identifier, "a"));
  tokens.push(QueryToken(TokenType::Identifier, "("));
  tokens.push(QueryToken(TokenType::Identifier, "v"));
  tokens.push(QueryToken(TokenType::Identifier, ","));
  tokens.push(QueryToken(TokenType::Identifier, "_"));
  tokens.push(QueryToken(TokenType::Identifier, "\""));
  tokens.push(QueryToken(TokenType::Identifier, "cenX *  ce3nX +ce nY*cenY"));
  tokens.push(QueryToken(TokenType::Identifier, "\""));
  tokens.push(QueryToken(TokenType::Identifier, "_"));
  tokens.push(QueryToken(TokenType::Identifier, ")"));
  PQLParser p = PQLParser();
  Query q = p.buildQuery(tokens);
  std::vector<Clause> clauses = q.clauses;
  SECTION("clauses: one AssignPatt clause is inside") {
    REQUIRE(clauses.size() == 1);
    Clause c = clauses.front();
    std::vector<QueryEntity> parameters = c.parameters;
    REQUIRE(c.clauseType == ClauseType::AssignPatt);
    REQUIRE(parameters[0].name == "a");
    REQUIRE(parameters[0].type == QueryEntityType::Assign);
    REQUIRE(parameters[1].name == "v");
    REQUIRE(parameters[1].type == QueryEntityType::Variable);
    REQUIRE(parameters[2].name == "_ cenX ce3nX * ce nY cenY * + _");
    REQUIRE(parameters[2].type == QueryEntityType::Expression);
  }
}

SCENARIO("Test pattern clause underscore") {
  queue<QueryToken> tokens;
  tokens.push(QueryToken(TokenType::Identifier, "assign"));
  tokens.push(QueryToken(TokenType::Identifier, "a"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  tokens.push(QueryToken(TokenType::Identifier, "variable"));
  tokens.push(QueryToken(TokenType::Identifier, "v"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  tokens.push(QueryToken(TokenType::Identifier, "Select"));
  tokens.push(QueryToken(TokenType::Identifier, "a"));
  tokens.push(QueryToken(TokenType::Identifier, "pattern"));
  tokens.push(QueryToken(TokenType::Identifier, "a"));
  tokens.push(QueryToken(TokenType::Identifier, "("));
  tokens.push(QueryToken(TokenType::Identifier, "v"));
  tokens.push(QueryToken(TokenType::Identifier, ","));
  tokens.push(QueryToken(TokenType::Identifier, "_"));
  tokens.push(QueryToken(TokenType::Identifier, ")"));
  PQLParser p = PQLParser();
  Query q = p.buildQuery(tokens);
  std::vector<Clause> clauses = q.clauses;
  SECTION("clauses: one AssignPatt clause is inside") {
    REQUIRE(clauses.size() == 1);
    Clause c = clauses.front();
    std::vector<QueryEntity> parameters = c.parameters;
    REQUIRE(c.clauseType == ClauseType::AssignPatt);
    REQUIRE(parameters[0].name == "a");
    REQUIRE(parameters[0].type == QueryEntityType::Assign);
    REQUIRE(parameters[1].name == "v");
    REQUIRE(parameters[1].type == QueryEntityType::Variable);
    REQUIRE(parameters[2].name == "_");
    REQUIRE(parameters[2].type == QueryEntityType::Underscore);
  }
}

SCENARIO("Test pattern clause strange case") {
  queue<QueryToken> tokens;
  tokens.push(QueryToken(TokenType::Identifier, "assign"));
  tokens.push(QueryToken(TokenType::Identifier, "a"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  tokens.push(QueryToken(TokenType::Identifier, "Select"));
  tokens.push(QueryToken(TokenType::Identifier, "a"));
  tokens.push(QueryToken(TokenType::Identifier, "pattern"));
  tokens.push(QueryToken(TokenType::Identifier, "a"));
  tokens.push(QueryToken(TokenType::Identifier, "("));
  tokens.push(QueryToken(TokenType::Identifier, "_"));
  tokens.push(QueryToken(TokenType::Identifier, ","));
  tokens.push(QueryToken(TokenType::Identifier, "_"));
  tokens.push(QueryToken(TokenType::Identifier, "\""));
  tokens.push(QueryToken(TokenType::Identifier, "0098 - sd *(tr - 0006)"));
  tokens.push(QueryToken(TokenType::Identifier, "\""));
  tokens.push(QueryToken(TokenType::Identifier, "_"));
  tokens.push(QueryToken(TokenType::Identifier, ")"));
  PQLParser p = PQLParser();
  Query q = p.buildQuery(tokens);
  std::vector<Clause> clauses = q.clauses;
  SECTION("clauses: one AssignPatt clause is inside") {
    REQUIRE(clauses.size() == 1);
    Clause c = clauses.front();
    std::vector<QueryEntity> parameters = c.parameters;
    REQUIRE(c.clauseType == ClauseType::AssignPatt);
    REQUIRE(parameters[0].name == "a");
    REQUIRE(parameters[0].type == QueryEntityType::Assign);
    REQUIRE(parameters[1].name == "_");
    REQUIRE(parameters[1].type == QueryEntityType::Underscore);
    REQUIRE(parameters[2].name == "_ 98 sd tr 6 - * - _");
    REQUIRE(parameters[2].type == QueryEntityType::Expression);
  }
}

// Scenarios that will throw exceptions
SCENARIO("select nothing") {
  queue<QueryToken> tokens;
  tokens.push(QueryToken(TokenType::Identifier, "variable"));
  tokens.push(QueryToken(TokenType::Identifier, "a"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  tokens.push(QueryToken(TokenType::Identifier, "Select"));
  PQLParser p = PQLParser();
  REQUIRE_THROWS_WITH(p.buildQuery(tokens), "Token Queue is empty!");
}

SCENARIO("select a entity that is not declared") {
  SECTION("in the Select target") {
    queue<QueryToken> tokens;
    tokens.push(QueryToken(TokenType::Identifier, "variable"));
    tokens.push(QueryToken(TokenType::Identifier, "a"));
    tokens.push(QueryToken(TokenType::Identifier, ";"));
    tokens.push(QueryToken(TokenType::Identifier, "Select"));
    tokens.push(QueryToken(TokenType::Identifier, "b"));
    PQLParser p = PQLParser();
    REQUIRE_THROWS_WITH(p.buildQuery(tokens),
                        "No matched synonym have been declared.");
  }
  SECTION("in the such that clause") {
    queue<QueryToken> tokens;
    tokens.push(QueryToken(TokenType::Identifier, "stmt"));
    tokens.push(QueryToken(TokenType::Identifier, "s"));
    tokens.push(QueryToken(TokenType::Identifier, ";"));
    tokens.push(QueryToken(TokenType::Identifier, "Select"));
    tokens.push(QueryToken(TokenType::Identifier, "s"));
    tokens.push(QueryToken(TokenType::Identifier, "such that"));
    tokens.push(QueryToken(TokenType::Identifier, "Parent*"));
    tokens.push(QueryToken(TokenType::Identifier, "("));
    tokens.push(QueryToken(TokenType::Identifier, "p"));
    tokens.push(QueryToken(TokenType::Identifier, ","));
    tokens.push(QueryToken(TokenType::Identifier, "_"));
    tokens.push(QueryToken(TokenType::Identifier, ")"));
    PQLParser p = PQLParser();
    REQUIRE_THROWS_WITH(p.buildQuery(tokens),
                        "No matched synonym have been declared.");
  }
  SECTION("in the pattern clause") {
    queue<QueryToken> tokens;
    tokens.push(QueryToken(TokenType::Identifier, "assign"));
    tokens.push(QueryToken(TokenType::Identifier, "a"));
    tokens.push(QueryToken(TokenType::Identifier, ";"));
    tokens.push(QueryToken(TokenType::Identifier, "Select"));
    tokens.push(QueryToken(TokenType::Identifier, "a"));
    tokens.push(QueryToken(TokenType::Identifier, "pattern"));
    tokens.push(QueryToken(TokenType::Identifier, "a1"));
    tokens.push(QueryToken(TokenType::Identifier, "("));
    tokens.push(QueryToken(TokenType::Identifier, "_"));
    tokens.push(QueryToken(TokenType::Identifier, ","));
    tokens.push(QueryToken(TokenType::Identifier, "_"));
    tokens.push(QueryToken(TokenType::Identifier, ")"));
    PQLParser p = PQLParser();
    REQUIRE_THROWS_WITH(p.buildQuery(tokens),
                        "No matched synonym have been declared.");
  }
}

SCENARIO("have underscore as the first argument for Modifies") {
  queue<QueryToken> tokens;
  tokens.push(QueryToken(TokenType::Identifier, "assign"));
  tokens.push(QueryToken(TokenType::Identifier, "a"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  tokens.push(QueryToken(TokenType::Identifier, "variable"));
  tokens.push(QueryToken(TokenType::Identifier, "v"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  tokens.push(QueryToken(TokenType::Identifier, "Select"));
  tokens.push(QueryToken(TokenType::Identifier, "a"));
  tokens.push(QueryToken(TokenType::Identifier, "such that"));
  tokens.push(QueryToken(TokenType::Identifier, "Modifies"));
  tokens.push(QueryToken(TokenType::Identifier, "("));
  tokens.push(QueryToken(TokenType::Identifier, "_"));
  tokens.push(QueryToken(TokenType::Identifier, ","));
  tokens.push(QueryToken(TokenType::Identifier, "v"));
  tokens.push(QueryToken(TokenType::Identifier, ")"));
  PQLParser p = PQLParser();
  REQUIRE_THROWS_WITH(p.buildQuery(tokens),
                      "semantically invalid to have underscore as the first "
                      "argument for Modifies");
}

SCENARIO("have constant synonym as the argument for clauses") {
  queue<QueryToken> tokens;
  tokens.push(QueryToken(TokenType::Identifier, "constant"));
  tokens.push(QueryToken(TokenType::Identifier, "c"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  tokens.push(QueryToken(TokenType::Identifier, "Select"));
  tokens.push(QueryToken(TokenType::Identifier, "c"));
  tokens.push(QueryToken(TokenType::Identifier, "such that"));
  tokens.push(QueryToken(TokenType::Identifier, "Uses"));
  tokens.push(QueryToken(TokenType::Identifier, "("));
  tokens.push(QueryToken(TokenType::Identifier, "\""));
  tokens.push(QueryToken(TokenType::Identifier, "proc1"));
  tokens.push(QueryToken(TokenType::Identifier, "\""));
  tokens.push(QueryToken(TokenType::Identifier, ","));
  tokens.push(QueryToken(TokenType::Identifier, "c"));
  tokens.push(QueryToken(TokenType::Identifier, ")"));
  PQLParser p = PQLParser();
  REQUIRE_THROWS_WITH(
      p.buildQuery(tokens),
      "invalid to have constant synonym as the argument for clauses");
}

SCENARIO("have procedure name as the first argument for Parent") {
  queue<QueryToken> tokens;
  tokens.push(QueryToken(TokenType::Identifier, "procedure"));
  tokens.push(QueryToken(TokenType::Identifier, "p"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  tokens.push(QueryToken(TokenType::Identifier, "Select"));
  tokens.push(QueryToken(TokenType::Identifier, "p"));
  tokens.push(QueryToken(TokenType::Identifier, "such that"));
  tokens.push(QueryToken(TokenType::Identifier, "Parent"));
  tokens.push(QueryToken(TokenType::Identifier, "("));
  tokens.push(QueryToken(TokenType::Identifier, "\""));
  tokens.push(QueryToken(TokenType::Identifier, "p"));
  tokens.push(QueryToken(TokenType::Identifier, "\""));
  tokens.push(QueryToken(TokenType::Identifier, ","));
  tokens.push(QueryToken(TokenType::Identifier, "6"));
  tokens.push(QueryToken(TokenType::Identifier, ")"));
  PQLParser p = PQLParser();
  REQUIRE_THROWS_WITH(p.buildQuery(tokens),
                      "invalid argument combination for clauses");
}

SCENARIO("no QueryToken matched for one expect QueryToken") {
  SECTION("no match for '('") {
    queue<QueryToken> tokens;
    tokens.push(QueryToken(TokenType::Identifier, "procedure"));
    tokens.push(QueryToken(TokenType::Identifier, "p"));
    tokens.push(QueryToken(TokenType::Identifier, ";"));
    tokens.push(QueryToken(TokenType::Identifier, "Select"));
    tokens.push(QueryToken(TokenType::Identifier, "p"));
    tokens.push(QueryToken(TokenType::Identifier, "such that"));
    tokens.push(QueryToken(TokenType::Identifier, "Follows"));
    tokens.push(QueryToken(TokenType::Identifier, "\""));
    tokens.push(QueryToken(TokenType::Identifier, "p"));
    tokens.push(QueryToken(TokenType::Identifier, "\""));
    tokens.push(QueryToken(TokenType::Identifier, ","));
    tokens.push(QueryToken(TokenType::Identifier, "6"));
    tokens.push(QueryToken(TokenType::Identifier, ")"));
    PQLParser p = PQLParser();
    REQUIRE_THROWS_WITH(p.buildQuery(tokens), "Expected '(' but got '\"'");
  }
  SECTION("no match for ';'") {
    queue<QueryToken> tokens;
    tokens.push(QueryToken(TokenType::Identifier, "procedure"));
    tokens.push(QueryToken(TokenType::Identifier, "p"));
    tokens.push(QueryToken(TokenType::Identifier, "Select"));
    tokens.push(QueryToken(TokenType::Identifier, "p"));
    tokens.push(QueryToken(TokenType::Identifier, "such that"));
    tokens.push(QueryToken(TokenType::Identifier, "Follows"));
    tokens.push(QueryToken(TokenType::Identifier, "("));
    tokens.push(QueryToken(TokenType::Identifier, "\""));
    tokens.push(QueryToken(TokenType::Identifier, "p"));
    tokens.push(QueryToken(TokenType::Identifier, "\""));
    tokens.push(QueryToken(TokenType::Identifier, ","));
    tokens.push(QueryToken(TokenType::Identifier, "6"));
    tokens.push(QueryToken(TokenType::Identifier, ")"));
    PQLParser p = PQLParser();
    REQUIRE_THROWS_WITH(p.buildQuery(tokens), "Expected ';' but got 'Select'");
  }
}

SCENARIO("no QueryToken matched in a list of expect tokens") {
  queue<QueryToken> tokens;
  tokens.push(QueryToken(TokenType::Identifier, "p"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  tokens.push(QueryToken(TokenType::Identifier, "Select"));
  tokens.push(QueryToken(TokenType::Identifier, "p"));
  tokens.push(QueryToken(TokenType::Identifier, "such that"));
  tokens.push(QueryToken(TokenType::Identifier, "Follows"));
  tokens.push(QueryToken(TokenType::Identifier, "("));
  tokens.push(QueryToken(TokenType::Identifier, "\""));
  tokens.push(QueryToken(TokenType::Identifier, "p"));
  tokens.push(QueryToken(TokenType::Identifier, "\""));
  tokens.push(QueryToken(TokenType::Identifier, ","));
  tokens.push(QueryToken(TokenType::Identifier, "6"));
  tokens.push(QueryToken(TokenType::Identifier, ")"));
  PQLParser p = PQLParser();
  REQUIRE_THROWS_WITH(p.buildQuery(tokens),
                      "Expected query entity type but got 'p'");
}

SCENARIO("syn-assign is not assignment synonym in pattern clause") {
  queue<QueryToken> tokens;
  tokens.push(QueryToken(TokenType::Identifier, "variable"));
  tokens.push(QueryToken(TokenType::Identifier, "v"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  tokens.push(QueryToken(TokenType::Identifier, "Select"));
  tokens.push(QueryToken(TokenType::Identifier, "v"));
  tokens.push(QueryToken(TokenType::Identifier, "pattern"));
  tokens.push(QueryToken(TokenType::Identifier, "v"));
  tokens.push(QueryToken(TokenType::Identifier, "("));
  tokens.push(QueryToken(TokenType::Identifier, "_"));
  tokens.push(QueryToken(TokenType::Identifier, ","));
  tokens.push(QueryToken(TokenType::Identifier, "_"));
  tokens.push(QueryToken(TokenType::Identifier, ")"));
  PQLParser p = PQLParser();
  REQUIRE_THROWS_WITH(
      p.buildQuery(tokens),
      "syn-assign must be declared as synonym of assignment for pattern");
}

SCENARIO("wrong query entity type for the fisrt parameter of pattern") {
  queue<QueryToken> tokens;
  tokens.push(QueryToken(TokenType::Identifier, "assign"));
  tokens.push(QueryToken(TokenType::Identifier, "a1"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  tokens.push(QueryToken(TokenType::Identifier, "procedure"));
  tokens.push(QueryToken(TokenType::Identifier, "p"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  tokens.push(QueryToken(TokenType::Identifier, "Select"));
  tokens.push(QueryToken(TokenType::Identifier, "p"));
  tokens.push(QueryToken(TokenType::Identifier, "pattern"));
  tokens.push(QueryToken(TokenType::Identifier, "a1"));
  tokens.push(QueryToken(TokenType::Identifier, "("));
  tokens.push(QueryToken(TokenType::Identifier, "p"));
  tokens.push(QueryToken(TokenType::Identifier, ","));
  tokens.push(QueryToken(TokenType::Identifier, "\""));
  tokens.push(QueryToken(TokenType::Identifier, "v+ 3"));
  tokens.push(QueryToken(TokenType::Identifier, "\""));
  tokens.push(QueryToken(TokenType::Identifier, ")"));
  PQLParser p = PQLParser();
  REQUIRE_THROWS_WITH(
      p.buildQuery(tokens),
      "Invalid query entity type for first parameter of pattern.");
}

SCENARIO("Invalid pattern expresion") {
  queue<QueryToken> tokens;
  tokens.push(QueryToken(TokenType::Identifier, "assign"));
  tokens.push(QueryToken(TokenType::Identifier, "a1"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  tokens.push(QueryToken(TokenType::Identifier, "Select"));
  tokens.push(QueryToken(TokenType::Identifier, "a1"));
  tokens.push(QueryToken(TokenType::Identifier, "pattern"));
  tokens.push(QueryToken(TokenType::Identifier, "a1"));
  tokens.push(QueryToken(TokenType::Identifier, "("));
  tokens.push(QueryToken(TokenType::Identifier, "_"));
  tokens.push(QueryToken(TokenType::Identifier, ","));
  tokens.push(QueryToken(TokenType::Identifier, "\""));
  tokens.push(QueryToken(TokenType::Identifier, "a+bs--sss"));
  tokens.push(QueryToken(TokenType::Identifier, "\""));
  tokens.push(QueryToken(TokenType::Identifier, ")"));
  PQLParser p = PQLParser();
  REQUIRE_THROWS_WITH(p.buildQuery(tokens), "Invalid expression");
}

SCENARIO("Delcare duplicated synonyms") {
  queue<QueryToken> tokens;
  tokens.push(QueryToken(TokenType::Identifier, "assign"));
  tokens.push(QueryToken(TokenType::Identifier, "a"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  tokens.push(QueryToken(TokenType::Identifier, "assign"));
  tokens.push(QueryToken(TokenType::Identifier, "a"));
  tokens.push(QueryToken(TokenType::Identifier, ";"));
  tokens.push(QueryToken(TokenType::Identifier, "Select"));
  tokens.push(QueryToken(TokenType::Identifier, "a"));
  PQLParser p = PQLParser();
  REQUIRE_THROWS_WITH(p.buildQuery(tokens), "'a' has been declared.");
}

SCENARIO("test BOOLEAN") {
	queue<QueryToken> tokens;
	tokens.push(QueryToken(TokenType::Identifier, "variable"));
	tokens.push(QueryToken(TokenType::Identifier, "a"));
	tokens.push(QueryToken(TokenType::Identifier, ";"));
	tokens.push(QueryToken(TokenType::Identifier, "Select"));
	tokens.push(QueryToken(TokenType::Identifier, "BOOLEAN"));
	PQLParser p = PQLParser();
	const Query q = p.buildQuery(tokens);
	const std::vector<QueryEntity> selectors = q.selectors;
	const vector<QueryEntity> tar = q.target;

	WHEN("Successfully parsed:") {
		SECTION("selectors: one QueryEntity is inside") {
			REQUIRE(selectors.size() == 1);
			const QueryEntity qe = selectors.front();
			REQUIRE(qe.name == "a");
			REQUIRE(qe.type == QueryEntityType::Variable);
		}
		SECTION("target") {
			REQUIRE(tar.front().name == "");
			REQUIRE(tar.front().type == QueryEntityType::Boolean);
		}
	}
}

SCENARIO("test tuple") {
	queue<QueryToken> tokens;
	tokens.push(QueryToken(TokenType::Identifier, "assign"));
	tokens.push(QueryToken(TokenType::Identifier, "a"));
	tokens.push(QueryToken(TokenType::Identifier, ","));
	tokens.push(QueryToken(TokenType::Identifier, "a1"));
	tokens.push(QueryToken(TokenType::Identifier, ";"));
	tokens.push(QueryToken(TokenType::Identifier, "Select"));
	tokens.push(QueryToken(TokenType::Identifier, "<"));
	tokens.push(QueryToken(TokenType::Identifier, "a"));
	tokens.push(QueryToken(TokenType::Identifier, ","));
	tokens.push(QueryToken(TokenType::Identifier, "a1"));
	tokens.push(QueryToken(TokenType::Identifier, ">"));
	PQLParser p = PQLParser();
	const Query q = p.buildQuery(tokens);
	const std::vector<QueryEntity> selectors = q.selectors;
	const vector<QueryEntity> tar = q.target;

	WHEN("Successfully parsed:") {
		SECTION("selectors: two QueryEntity is inside") {
			REQUIRE(selectors.size() == 2);
		}
		SECTION("2 tuple targets") {
			REQUIRE(tar.size() == 2);
			REQUIRE(tar[0].name == "a");
			REQUIRE(tar[0].type == QueryEntityType::Assign);
			REQUIRE(tar[1].name == "a1");
			REQUIRE(tar[1].type == QueryEntityType::Assign);
		}
	}
}

SCENARIO("test tuple2") {
	queue<QueryToken> tokens;
	tokens.push(QueryToken(TokenType::Identifier, "assign"));
	tokens.push(QueryToken(TokenType::Identifier, "a"));
	tokens.push(QueryToken(TokenType::Identifier, ","));
	tokens.push(QueryToken(TokenType::Identifier, "a1"));
	tokens.push(QueryToken(TokenType::Identifier, ";"));
	tokens.push(QueryToken(TokenType::Identifier, "Select"));
	tokens.push(QueryToken(TokenType::Identifier, "<"));
	tokens.push(QueryToken(TokenType::Identifier, "a"));
	tokens.push(QueryToken(TokenType::Identifier, ","));
	tokens.push(QueryToken(TokenType::Identifier, "a1"));
	tokens.push(QueryToken(TokenType::Identifier, ","));
	tokens.push(QueryToken(TokenType::Identifier, "a1"));
	tokens.push(QueryToken(TokenType::Identifier, "."));
	tokens.push(QueryToken(TokenType::Identifier, "stmt#"));
	tokens.push(QueryToken(TokenType::Identifier, ">"));
	PQLParser p = PQLParser();
	const Query q = p.buildQuery(tokens);
	const std::vector<QueryEntity> selectors = q.selectors;
	const vector<QueryEntity> tar = q.target;

	WHEN("Successfully parsed:") {
		SECTION("selectors: two QueryEntity is inside") {
			REQUIRE(selectors.size() == 2);
		}
		SECTION("2 tuple targets") {
			REQUIRE(tar.size() == 3);
			REQUIRE(tar[0].name == "a");
			REQUIRE(tar[0].type == QueryEntityType::Assign);
			REQUIRE(tar[1].name == "a1");
			REQUIRE(tar[1].type == QueryEntityType::Assign);
			REQUIRE(tar[2].name == "a1.stmt#");
			REQUIRE(tar[2].type == QueryEntityType::Attrref);
		}
	}
}

SCENARIO("test with clause") {
	queue<QueryToken> tokens;
	tokens.push(QueryToken(TokenType::Identifier, "assign"));
	tokens.push(QueryToken(TokenType::Identifier, "a"));
	tokens.push(QueryToken(TokenType::Identifier, ";"));
	tokens.push(QueryToken(TokenType::Identifier, "Select"));
	tokens.push(QueryToken(TokenType::Identifier, "a"));
	tokens.push(QueryToken(TokenType::Identifier, "with"));
	tokens.push(QueryToken(TokenType::Identifier, "a"));
	tokens.push(QueryToken(TokenType::Identifier, "."));
	tokens.push(QueryToken(TokenType::Identifier, "stmt#"));
	tokens.push(QueryToken(TokenType::Identifier, "="));
	tokens.push(QueryToken(TokenType::Identifier, "5"));
	tokens.push(QueryToken(TokenType::Identifier, "and"));
	tokens.push(QueryToken(TokenType::Identifier, "a"));
	tokens.push(QueryToken(TokenType::Identifier, "."));
	tokens.push(QueryToken(TokenType::Identifier, "varName"));
	tokens.push(QueryToken(TokenType::Identifier, "="));
	tokens.push(QueryToken(TokenType::Identifier, "\""));
	tokens.push(QueryToken(TokenType::Identifier, "b"));
	tokens.push(QueryToken(TokenType::Identifier, "\""));

	PQLParser p = PQLParser();
	const Query q = p.buildQuery(tokens);
	const std::vector<QueryEntity> selectors = q.selectors;
	const vector<QueryEntity> tar = q.target;

	WHEN("Successfully parsed:") {
		SECTION("selectors: two QueryEntity is inside") {
			REQUIRE(selectors.size() == 2);
		}
		SECTION("2 tuple targets") {
			REQUIRE(tar.size() == 3);
			REQUIRE(tar[0].name == "a");
			REQUIRE(tar[0].type == QueryEntityType::Assign);
			REQUIRE(tar[1].name == "a1");
			REQUIRE(tar[1].type == QueryEntityType::Assign);
			REQUIRE(tar[2].name == "a1.stmt#");
			REQUIRE(tar[2].type == QueryEntityType::Attrref);
		}
	}
}