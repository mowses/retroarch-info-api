#include "OSystem.hxx"
#include "HighScoresManager.cxx"

json current_score(OSystem& osystem)
{
  json score = json::object();
  HighScoresManager highScoresManager(osystem);
  
  score["numVariations"] = highScoresManager.numVariations();
  score["variation"] = highScoresManager.variation();
  score["score"] = highScoresManager.score();
  score["scoreInvert"] = highScoresManager.scoreInvert();
  score["specialLabel"] = highScoresManager.specialLabel();
  score["special"] = highScoresManager.special();
  score["notes"] = highScoresManager.notes();
  score["md5Props"] = highScoresManager.md5Props();

  return score;
}