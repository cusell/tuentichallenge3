<?php
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, 'silence.contest.tuenti.net');
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERAGENT, 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.31 (KHTML, like Gecko) Chrome/26.0.1410.43 Safari/537.31');
  curl_setopt($ch,CURLOPT_COOKIE, "adminsession=true");
  $html = curl_exec($ch);
  echo $html;
?>
