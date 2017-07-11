int main()
{
    try
    {
        // regular code
    }
    catch (soci::mysql_soci_error const & e)
    {
        cerr << "MySQL error: " << e.err_num_
            << " " << e.what() << endl;
    }
    catch (soci::exception const & e)
    {
        cerr << "Some other error: " << e.what() << endl;
    }
}
