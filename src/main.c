#include <clang-c/Index.h>
#include <stdio.h>

void printCXString(CXString s)
{
  printf("%s", clang_getCString(s));
  clang_disposeString(s);
}

void get_cursor_type(CXCursor cursor){
  CXType cursor_type = clang_getCursorType(cursor);
  printCXString(clang_getTypeSpelling(cursor_type));
}

void get_cursor_spelling(CXCursor cursor){
  CXString cursor_spelling = clang_getCursorSpelling(cursor);
  printCXString(cursor_spelling);
}

 enum CXChildVisitResult enum_visitor(CXCursor cursor, CXCursor parent, CXClientData client_data) {
  if(clang_getCursorKind(cursor) == CXCursor_IntegerLiteral){
    long long enum_const_value = clang_getEnumConstantDeclValue(parent);
    printf("IntegerLiteral\t %lld \t\tParent = ", enum_const_value);
    get_cursor_spelling(parent);
    printf("\n");
  }

  else if(clang_getCursorKind(cursor) == CXCursor_EnumConstantDecl){
    printf("EnumConstantDecl\t");
    get_cursor_spelling(cursor);
    printf("\tParent = ");
    get_cursor_spelling(parent);
    printf("\n");
  }
  return CXChildVisit_Recurse;
}

void enum_handler(CXCursor cursor){
  printf("EnumDecl\t");
  get_cursor_spelling(cursor);
  printf("\n");
  clang_visitChildren(cursor, enum_visitor, 0);
}

enum CXChildVisitResult visitor(CXCursor cursor, CXCursor parent, CXClientData client_data) {
  if(clang_getCursorKind(cursor) == CXCursor_EnumDecl){
    enum_handler(cursor);
  }
  return CXChildVisit_Continue;
}

int main(int argc, char **argv) {
  CXIndex index = clang_createIndex(1, 0);
  CXTranslationUnit TU = clang_parseTranslationUnit(index, 0, argv, argc, 0, 0, CXTranslationUnit_None);
  CXCursor cursor = clang_getTranslationUnitCursor(TU);
  clang_visitChildren(cursor, visitor, 0);
  clang_disposeTranslationUnit(TU);
  clang_disposeIndex(index);
  return 0;
}
