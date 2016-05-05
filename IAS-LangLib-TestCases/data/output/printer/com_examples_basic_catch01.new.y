PROGRAM com::examples::basic::catch01(
            VAR p1 AS Integer : "IAS/DM/Default",
            VAR input AS Customer : "http://www.examples.org/akc",
            VAR output AS Customer : "http://www.examples.org/akc")  BEGIN
    output=COPYOF(input);

    TRY     BEGIN
      com::examples::utility(10,output);
    END
    CATCH (
      VAR e AS Integer : "IAS/DM/Default" )     BEGIN
      output.firstname="failed 1";
    END    CATCH (
      VAR a AS Customer : "http://www.examples.org/akc" )     BEGIN
      output.firstname="failed 2";
    END;
  END;
