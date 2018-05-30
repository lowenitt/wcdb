/*
 * Tencent is pleased to support the open source community by making
 * WCDB available.
 *
 * Copyright (C) 2017 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *       https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <WCDB/WINQ.h>

namespace WCDB {

const ResultColumn &ResultColumn::all()
{
    static const ResultColumn *s_all =
        new ResultColumn(Lang::ResultColumn::Type::Star);
    return *s_all;
}

ResultColumn::ResultColumn(const Expression::All &all)
{
    setType(Lang::ResultColumn::Type::Star);
}

ResultColumn::ResultColumn(const Lang::ResultColumn::Type &type)
{
    setType(Lang::ResultColumn::Type::Star);
}

void ResultColumn::setType(const Lang::ResultColumn::Type &type)
{
    Lang::ResultColumn &lang = getMutableLang();
    lang.type = type;
}

ResultColumn::ResultColumn(const Expression &expression)
{
    setupWithExpression(expression);
}

ResultColumn &ResultColumn::withTable(const std::string &tableName)
{
    Lang::ResultColumn &lang = getMutableLang();
    WINQRemedialAssert(lang.type == Lang::ResultColumn::Type::Star);
    lang.tableName.assign(tableName);
    return *this;
}

ResultColumn &ResultColumn::as(const Column &columnAlias)
{
    Lang::ResultColumn &lang = getMutableLang();
    WINQRemedialAssert(lang.type == Lang::ResultColumn::Type::Expr);
    lang.columnAlias.assign(columnAlias.getCOWLang());
    return *this;
}

void ResultColumn::setupWithExpression(const Expression &expression)
{
    Lang::ResultColumn &lang = getMutableLang();
    lang.type = Lang::ResultColumn::Type::Expr;
    lang.expr.assign(expression.getCOWLang());
}

ResultColumn::operator std::list<ResultColumn>() const
{
    return {*this};
}

} // namespace WCDB
