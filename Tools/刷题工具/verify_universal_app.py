import json
import re
from pathlib import Path

html = (Path(__file__).resolve().parents[1] / "outputs" / "通用刷题工具.html").read_text(encoding="utf-8")
match = re.search(r'<script id="question-data" type="application/json">(.*?)</script>', html, re.S)
if not match:
    raise SystemExit("question-data script not found")
questions = json.loads(match.group(1))
print("count", len(questions))
print("single", sum(q["type"] == "single" for q in questions))
print("multi", sum(q["type"] == "multi" for q in questions))
print("judge", sum(q["type"] == "judge" for q in questions))
print("has_import", "extractDocxText" in html and "parseTextQuestions" in html)
