#include <QtTest>

// add necessary includes here
#include "lexer.h"
#include "token.h"
class LexerTest : public QObject
{
    Q_OBJECT

private slots:
    void basicExpression();
};

void LexerTest::basicExpression()
{
    QQueue<Token> tokens = lexer("(12 \"test\" +Identifikator5  ~ ~@ ' `)");
    QVERIFY(tokens.size() == 10);

    Token token = tokens.first();
    tokens.pop_front();
    Token cmp;
    cmp.line = 0;
    cmp.type = TokenType::lParen;
    cmp.value = QVariant('(');
    QVERIFY(token == cmp);

    token = tokens.first();
    tokens.pop_front();
    cmp.line = 0;
    cmp.type = TokenType::number;
    cmp.value = QVariant(12);
    QVERIFY(token == cmp);

    token = tokens.first();
    tokens.pop_front();
    cmp.line = 0;
    cmp.type = TokenType::string;
    cmp.value = QVariant("test");
    QVERIFY(token == cmp);

    token = tokens.first();
    tokens.pop_front();
    cmp.line = 0;
    cmp.type = TokenType::identifier;
    cmp.value = QVariant("+Identifikator5");
    QVERIFY(token == cmp);

    token = tokens.first();
    tokens.pop_front();
    cmp.line = 0;
    cmp.type = TokenType::eval;
    cmp.value = QVariant("~");
    QVERIFY(token == cmp);

    token = tokens.first();
    tokens.pop_front();
    cmp.line = 0;
    cmp.type = TokenType::unrollEval;
    cmp.value = QVariant("~@");
    QVERIFY(token == cmp);

    token = tokens.first();
    tokens.pop_front();
    cmp.line = 0;
    cmp.type = TokenType::quote;
    cmp.value = QVariant("'");
    QVERIFY(token == cmp);

    token = tokens.first();
    tokens.pop_front();
    cmp.line = 0;
    cmp.type = TokenType::quasiQuote;
    cmp.value = QVariant("`");
    QVERIFY(token == cmp);

    token = tokens.first();
    tokens.pop_front();
    cmp.line = 0;
    cmp.type = TokenType::rParen;
    cmp.value = QVariant(')');
    QVERIFY(token == cmp);

    token = tokens.first();
    cmp.line = 0;
    cmp.type = TokenType::eof;
    cmp.value = QVariant("");
    QVERIFY(token.type == TokenType::eof);
}

QTEST_APPLESS_MAIN(LexerTest)

#include "tst_lexertest.moc"
