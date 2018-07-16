IMPORT std::default;

PROGRAM wrap::calladd(VAR v AS Integer)
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
" INSERT INTO T1
   v => c1
");

PROGRAM wrap::select(VAR v AS Integer)
RETURNS ARRAY OF String
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
" SELECT ARRAY INTO result
    c1 => ''
  FROM T1
 WHERE 
  c1 = v
");

PROGRAM adhoc(VAR ctx     AS Context  : "http://www.invenireaude.org/qsystem/workers",
			   VAR params  AS RunParameters : "http://www.invenireaude.org/qsystem/workers")
BEGIN

  wrap::calladd((params.args[0] AS Integer));

  params.args = wrap::select((params.args[1] AS Integer));
  
  std::save("stdout",params);
  
END;