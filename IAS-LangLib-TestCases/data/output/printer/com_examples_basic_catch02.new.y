PROGRAM com::examples::basic::catch02(
            VAR p1 AS Integer : "IAS/DM/Default",
            VAR input AS Customer : "http://www.examples.org/akc",
            VAR output AS Customer : "http://www.examples.org/akc")  BEGIN
    output=COPYOF(input);

    TRY     BEGIN

      VAR a AS Address : "http://www.examples.org/akcf";

      a=NEW Address : "http://www.examples.org/akcf";
      a.street="Wyjatkowa";
      a.block=999;

      THROW a;
    END
    CATCH (
      VAR e AS Integer : "IAS/DM/Default" )     BEGIN
      output.lastname="Failure";
    END    CATCH (
      VAR c AS Customer : "http://www.examples.org/akc" )     BEGIN
      output.lastname="Failure";
    END    CATCH (
      VAR a AS Address : "http://www.examples.org/akc" )     BEGIN
      output.lastname="Success";
      output.address[0]=a;
    END;
  END;
