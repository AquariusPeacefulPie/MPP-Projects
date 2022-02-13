add_test( test.basic /Users/jeremyperrin/Documents/FAC/3eme_Annee_CMI_Informatique/semestre_6/PMP/parser/build/testParser [==[--gtest_filter=test.basic]==] --gtest_also_run_disabled_tests)
set_tests_properties( test.basic PROPERTIES WORKING_DIRECTORY /Users/jeremyperrin/Documents/FAC/3eme_Annee_CMI_Informatique/semestre_6/PMP/parser/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( testParser_TESTS test.basic)
